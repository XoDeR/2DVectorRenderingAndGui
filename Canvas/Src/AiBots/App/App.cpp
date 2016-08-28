#include "App.h"

#include <bgfx.h>
#include <bx/string.h>
#include <bx/timer.h>

#include "imgui/imgui.h"
#include "nanovg/nanovg.h"

#include <time.h>

#include "Core/Base/constants.h"
#include "Core/Math/MathFn.h"
#include "Core/Memory/Memory.h"
#include "Core/Time/PrecisionTimer.h"
#include "Core/Debug/DebugConsole.h"
#include "Core/Debug/Log.h"

#include "Renderer/Canvas.h"

#include "Config/UserOptions.h"

#include "Events/InputEvents.h"

void App::init()
{
	Rio::MemoryGlobalsFn::init();
	// BGFX
	bgfx::init();
	bgfx::reset(width, height, reset);
	// Enable debug text.
	bgfx::setDebug(debug);
	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);
	// ImGui
	imguiCreate();

	// NVG
	nvg = nvgCreate(1, 0);
	bgfx::setViewSeq(0, true);

	loadDemoData(nvg, &data);

	// load texture
	char file[128];
	bx::snprintf(file, 128, "images/Icon-100.png");
	textureHandle = nvgCreateImage(nvg, file, 0);
	if (textureHandle == bgfx::invalidHandle)
	{
		printf("Could not load %s.\n", file);
		RIO_FATAL("Could not load texture"); // exit app
	}
	////

	//bndSetFont(nvgCreateFont(nvg, "droidsans", "font/droidsans.ttf"));
	//bndSetIconImage(nvgCreateImage(nvg, "images/blender_icons16.png", 0));

	timeOffset = bx::getHPCounter();

	// create window with WindowWidth and WindowHeight

	// seed random number generator
	srand((unsigned)time(nullptr));

	// create the game
	//// init()
	PrecisionTimer timer(frameRate);
	timer.startTimer();
}

void App::update()
{
	// inputSystem update with mouse state
	if (!!mouseState.m_buttons[entry::MouseButton::Left]
		|| !!mouseState.m_buttons[entry::MouseButton::Middle]
		|| !!mouseState.m_buttons[entry::MouseButton::Right]
		)
	{
		inputSystem.processLocationSelected(mouseState.m_mx, mouseState.m_my);
	}

	int64_t now = bx::getHPCounter();
	const double freq = double(bx::getHPFrequency());
	float time = (float)((now - this->timeOffset) / freq);

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, this->width, this->height);

	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::touch(0);

	// Use debug font to print information about this example.
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 1, 0x4f, "VG Test");
	bgfx::dbgTextPrintf(0, 2, 0x6f, "vector graphics rendering library.");

	nvgBeginFrame(nvg, width, height, 1.0f);

	//renderDemo(nvg, float(width), float(height), &data);

	renderSprite(nvg, float(width), float(height), textureHandle);

	Canvas::getInstance()->startDrawing(nvg);

	//// render()

	Canvas::getInstance()->stopDrawing(nvg);

	//drawDropDown(nvg, "Test DropDown", 100, 200, 100, 300);

	nvgEndFrame(nvg);

	imguiBeginFrame(mouseState.m_mx
		, mouseState.m_my
		, (mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
		| (mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
		, 0
		, width
		, height
		);

	inputSystem.processGui();
	imguiEndFrame();

	// Advance to next frame
	// Rendering thread will be kicked to process submitted rendering primitives
	bgfx::frame();
}

void App::shutdown()
{
	//// shutdown

	//// free texture
	nvgDeleteImage(nvg, textureHandle);
	////

	freeDemoData(nvg, &data);

	nvgDelete(nvg);

	imguiDestroy();

	// Shutdown bgfx.
	bgfx::shutdown();

	Rio::MemoryGlobalsFn::shutdown();
}

int App::loadDemoData(struct NVGcontext* vg, struct DemoData* data)
{
	for (uint32_t ii = 0; ii < 12; ++ii)
	{
		char file[128];
		bx::snprintf(file, 128, "images/image%d.jpg", ii + 1);
		data->images[ii] = nvgCreateImage(vg, file, 0);
		if (data->images[ii] == bgfx::invalidHandle)
		{
			printf("Could not load %s.\n", file);
			return -1;
		}
	}

	data->fontIcons = nvgCreateFont(vg, "icons", "font/entypo.ttf");
	if (data->fontIcons == -1)
	{
		printf("Could not add font icons.\n");
		return -1;
	}

	data->fontNormal = nvgCreateFont(vg, "sans", "font/roboto-regular.ttf");
	if (data->fontNormal == -1)
	{
		printf("Could not add font italic.\n");
		return -1;
	}

	data->fontBold = nvgCreateFont(vg, "sans-bold", "font/roboto-bold.ttf");
	if (data->fontBold == -1)
	{
		printf("Could not add font bold.\n");
		return -1;
	}

	return 0;
}

void App::freeDemoData(struct NVGcontext* vg, struct DemoData* data)
{
	int i;

	if (vg == NULL)
		return;

	for (i = 0; i < 12; i++)
		nvgDeleteImage(vg, data->images[i]);
}

void App::renderSprite(struct NVGcontext* vg, float width, float height, uint16_t textureHandle)
{
	nvgSave(vg);

	struct NVGpaint imgPaint;
	int imgw;
	int imgh;
	nvgImageSize(vg, textureHandle, &imgw, &imgh);
	imgPaint = nvgImagePattern(vg, 50, 50, imgw, imgh, 0.0f / 180.0f*NVG_PI, textureHandle, 0);
	nvgBeginPath(vg);
	nvgRect(vg, 50, 50, imgw, imgh);
	nvgFillPaint(vg, imgPaint);
	nvgFill(vg);

	nvgRestore(vg);
}
