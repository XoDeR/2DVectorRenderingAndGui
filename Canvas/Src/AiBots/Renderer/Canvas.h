// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Debug/Error.h"
#include "Core/Math/Vector2.h"

#include <string>
#include <vector>

#include "nanovg/nanovg.h"

// 2D vector graphics
// always call startDrawing() prior to any rendering, and complete any rendering with stopDrawing()

const int colorsCount = 16;

const NVGcolor colors[colorsCount] =
{
	nvgRGB(255, 0, 0),
	nvgRGB(0, 0, 255),
	nvgRGB(0, 255, 0),
	nvgRGB(0, 0, 0),
	nvgRGB(255, 200, 200),
	nvgRGB(200, 200, 200),
	nvgRGB(255, 255, 0),
	nvgRGB(255, 170, 0),
	nvgRGB(255, 0, 170),
	nvgRGB(133, 90, 0),
	nvgRGB(255, 255, 255),
	nvgRGB(0, 100, 0), // dark green
	nvgRGB(0, 255, 255), // light blue
	nvgRGB(200, 200, 200), // light grey
	nvgRGB(255, 230, 230), // light pink
	nvgRGBA(0, 0, 0, 0), // hollow (opacity = 0)
};

struct Pen
{
	Pen()
	{}
	Pen(float strokeWidth, NVGcolor strokeColor)
		: strokeWidth(strokeWidth)
		, strokeColor(strokeColor)
	{}
	float strokeWidth = 1.0f;
	NVGcolor strokeColor = nvgRGB(0, 0, 0); // black is default
};

struct Brush
{
	Brush()
	{}
	Brush(NVGcolor fillColor)
		: fillColor(fillColor)
	{}
	NVGcolor fillColor = nvgRGB(255, 255, 255); // default fillColor is white
};

class Canvas
{
public:
	// colors
	enum
	{
		red,
		blue,
		green,
		black,
		pink,
		grey,
		yellow,
		orange,
		purple,
		brown,
		white,
		DarkGreen,
		light_blue,
		light_grey,
		light_pink,
		hollow
	};

	~Canvas();

	static Canvas* getInstance();

	void selectBlackPen();
	void selectWhitePen();
	void selectRedPen();
	void selectGreenPen();
	void selectBluePen();
	void selectGreyPen();
	void selectPinkPen();
	void selectYellowPen();
	void selectOrangePen();
	void selectPurplePen();
	void selectBrownPen();

	void selectDarkGreenPen();
	void selectLightBluePen();
	void selectLightGreyPen();
	void selectLightPinkPen();

	void selectThickBlackPen();
	void selectThickWhitePen();
	void selectThickRedPen();
	void selectThickGreenPen();
	void selectThickBluePen();

	void selectBlackBrush();
	void selectWhiteBrush();
	void selectHollowBrush(); // opacity == 0
	void selectGreenBrush();
	void selectRedBrush();
	void selectBlueBrush();
	void selectGreyBrush();
	void selectBrownBrush();
	void selectYellowBrush();
	void selectLightBlueBrush();
	void selectDarkGreenBrush();
	void selectOrangeBrush();

	// ALWAYS call this before drawing
	void startDrawing(NVGcontext* context);
	// ALWAYS call this after drawing
	void stopDrawing(NVGcontext* hdc);

	// Text
	void drawTextAtPosition(int x, int y, const std::string& s);
	void drawTextAtPosition(double x, double y, const std::string& s);
	void drawTextAtPosition(Vector2 position, const std::string& s);
	void setTransparentText();
	void setTextColor(int color);
	void setTextColor(int r, int g, int b);

	// Dots
	void drawDot(Vector2 pos, NVGcolor color);
	void drawDot(int x, int y, NVGcolor color);

	// Lines
	void drawLine(Vector2 from, Vector2 to);
	void drawLine(int a, int b, int x, int y);
	void drawLine(double a, double b, double x, double y);
	void drawPolyLine(const std::vector<Vector2>& points);
	void drawLineWithArrow(Vector2 from, Vector2 to, double size);
	void drawCross(Vector2 pos, int diameter);

	// Geometry shapes drawing
	void drawRect(int left, int top, int right, int bot);
	void drawRect(double left, double top, double right, double bot);
	void drawClosedShape(const std::vector<Vector2>& points);
	void drawCircle(Vector2 pos, double radius);
	void drawCircle(double x, double y, double radius);
	void drawCircle(int x, int y, double radius);

	void setPenColor(int color);
private:
	// constructor is private
	Canvas();
	// copy ctor and assignment should be private
	Canvas(const Canvas&);
	Canvas& operator=(const Canvas&);

	Pen selectPen(Pen& pen);
	Brush selectBrush(Brush& brush);

	Pen currentPen;
	Pen oldPen;

	// all the pens
	Pen blackPen;
	Pen whitePen;
	Pen redPen;
	Pen greenPen;
	Pen bluePen;
	Pen greyPen;
	Pen pinkPen;
	Pen orangePen;
	Pen yellowPen;
	Pen purplePen;
	Pen brownPen;

	Pen darkGreenPen;
	Pen lightBluePen;
	Pen lightGreyPen;
	Pen lightPinkPen;

	Pen thickBlackPen;
	Pen thickWhitePen;
	Pen thickRedPen;
	Pen thickGreenPen;
	Pen thickBluePen;

	Brush currentBrush;
	Brush oldBrush;

	// brushes
	Brush blackBrush;
	Brush whiteBrush;
	Brush hollowBrush;
	Brush redBrush;
	Brush greenBrush;
	Brush blueBrush;
	Brush greyBrush;
	Brush brownBrush;
	Brush yellowBrush;
	Brush orangeBrush;

	Brush lightBlueBrush;
	Brush darkGreenBrush;

	NVGcontext* context = nullptr;
};
