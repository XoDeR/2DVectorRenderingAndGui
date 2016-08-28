// Copyright (c) 2015, 2016 Volodymyr Syvochka
#include "Renderer/Canvas.h"

Canvas* Canvas::getInstance()
{
	static Canvas instance;
	return &instance;
}

Canvas::Canvas()
{
	blackPen = Pen(1, colors[black]);
	whitePen = Pen(1, colors[white]);
	redPen = Pen(1, colors[red]);
	greenPen = Pen(1, colors[green]);
	bluePen = Pen(1, colors[blue]);
	greyPen = Pen(1, colors[grey]);
	pinkPen = Pen(1, colors[pink]);
	yellowPen = Pen(1, colors[yellow]);
	orangePen = Pen(1, colors[orange]);
	purplePen = Pen(1, colors[purple]);
	brownPen = Pen(1, colors[brown]);

	darkGreenPen = Pen(1, colors[DarkGreen]);

	lightBluePen = Pen(1, colors[light_blue]);
	lightGreyPen = Pen(1, colors[light_grey]);
	lightPinkPen = Pen(1, colors[light_pink]);

	thickBlackPen = Pen(2, colors[black]);
	thickWhitePen = Pen(2, colors[white]);
	thickRedPen = Pen(2, colors[red]);
	thickGreenPen = Pen(2, colors[green]);
	thickBluePen = Pen(2, colors[blue]);

	blackBrush = Brush(colors[black]);
	whiteBrush = Brush(colors[white]);
	hollowBrush = Brush(colors[hollow]);

	greenBrush = Brush(colors[green]);
	redBrush = Brush(colors[red]);
	blueBrush = Brush(colors[blue]);
	greyBrush = Brush(colors[grey]);
	brownBrush = Brush(colors[brown]);
	yellowBrush = Brush(colors[yellow]);
	lightBlueBrush = Brush(colors[light_blue]);
	darkGreenBrush = Brush(colors[DarkGreen]);
	orangeBrush = Brush(colors[orange]);

	// default
	currentPen = blackPen;
	//selectPen(currentPen);
	currentBrush = greenBrush;
	//selectBrush(currentBrush);
}

Canvas::~Canvas()
{
}

Pen Canvas::selectPen(Pen& pen)
{
	nvgStrokeWidth(context, pen.strokeWidth);
	nvgStrokeColor(context, pen.strokeColor);
	Pen oldPen = currentPen;
	currentPen = pen;
	return oldPen;
}

Brush Canvas::selectBrush(Brush& brush)
{
	nvgFillColor(context, brush.fillColor);
	Brush oldBrush = currentBrush;
	currentBrush = brush;
	return oldBrush;
}

void Canvas::startDrawing(NVGcontext* context)
{
	RIO_ASSERT(context != NULL, "");

	this->context = context;

	// get the current pen
	oldPen = selectPen(blackPen);
	// select it back in
	selectPen(oldPen);

	oldBrush = selectBrush(blackBrush);
	selectBrush(oldBrush);
}

void Canvas::stopDrawing(NVGcontext* hdc)
{
	RIO_ASSERT_NOT_NULL(hdc);

	selectPen(oldPen);
	selectBrush(oldBrush);

	context = nullptr;
}

void Canvas::selectBlackPen()
{
	if (context){ selectPen(blackPen); }
}

void Canvas::selectWhitePen()
{
	if (context){ selectPen(whitePen); }
}

void Canvas::selectRedPen()
{
	if (context){ selectPen(redPen); }
}

void Canvas::selectGreenPen()
{
	if (context){ selectPen(greenPen); }
}

void Canvas::selectBluePen()
{
	if (context){ selectPen(bluePen); }
}

void Canvas::selectGreyPen()
{
	if (context){ selectPen(greyPen); }
}

void Canvas::selectPinkPen()
{
	if (context){ selectPen(pinkPen); }
}

void Canvas::selectYellowPen()
{
	if (context){ selectPen(yellowPen); }
}

void Canvas::selectOrangePen()
{
	if (context){ selectPen(orangePen); }
}

void Canvas::selectPurplePen()
{
	if (context){ selectPen(purplePen); }
}

void Canvas::selectBrownPen()
{
	if (context){ selectPen(brownPen); }
}

void Canvas::selectDarkGreenPen()
{
	if (context){ selectPen(darkGreenPen); }
}

void Canvas::selectLightBluePen()
{
	if (context){ selectPen(lightBluePen); }
}

void Canvas::selectLightGreyPen()
{
	if (context){ selectPen(lightGreyPen); }
}

void Canvas::selectLightPinkPen()
{
	if (context){ selectPen(lightPinkPen); }
}

void Canvas::selectThickBlackPen()
{
	if (context){ selectPen(thickBlackPen); }
}

void Canvas::selectThickWhitePen()
{
	if (context){ selectPen(thickWhitePen); }
}

void Canvas::selectThickRedPen()
{
	if (context){ selectPen(thickRedPen); }
}

void Canvas::selectThickGreenPen()
{
	if (context){ selectPen(thickGreenPen); }
}

void Canvas::selectThickBluePen()
{
	if (context){ selectPen(thickBluePen); }
}

void Canvas::selectBlackBrush()
{
	if (context) selectBrush(blackBrush);
}

void Canvas::selectWhiteBrush()
{
	if (context) selectBrush(whiteBrush);
}

void Canvas::selectHollowBrush()
{
	if (context) selectBrush(hollowBrush);
}

void Canvas::selectGreenBrush()
{
	if (context) selectBrush(greenBrush);
}

void Canvas::selectRedBrush()
{
	if (context) selectBrush(redBrush);
}

void Canvas::selectBlueBrush()
{
	if (context) selectBrush(blueBrush);
}

void Canvas::selectGreyBrush()
{
	if (context) selectBrush(greyBrush);
}

void Canvas::selectBrownBrush()
{
	if (context) selectBrush(brownBrush);
}

void Canvas::selectYellowBrush()
{
	if (context) selectBrush(yellowBrush);
}

void Canvas::selectLightBlueBrush()
{
	if (context) selectBrush(lightBlueBrush);
}

void Canvas::selectDarkGreenBrush()
{
	if (context) selectBrush(darkGreenBrush);
}

void Canvas::selectOrangeBrush()
{
	if (context) selectBrush(orangeBrush);
}

void Canvas::drawTextAtPosition(int x, int y, const std::string& s)
{
	nvgText(context, x, y, s.c_str(), NULL);
}

void Canvas::drawTextAtPosition(double x, double y, const std::string& s)
{
	nvgText(context, x, y, s.c_str(), NULL);
}

void Canvas::drawTextAtPosition(Vector2 position, const std::string& s)
{
	nvgText(context, position.x, position.y, s.c_str(), NULL);
}

void Canvas::setTransparentText()
{
	nvgFillColor(context, nvgRGBA(0, 0, 0, 0));
}

void Canvas::setTextColor(int color)
{
	RIO_ASSERT(color < colorsCount, "");
	nvgFillColor(context, colors[color]);
}

void Canvas::setTextColor(int r, int g, int b)
{
	nvgFillColor(context, nvgRGBA(r, g, b, 1));
}

void Canvas::drawDot(Vector2 pos, NVGcolor color)
{
	Brush oldBrush = selectBrush(Brush(color));

	float radius = 1.0f;
	nvgCircle(context, static_cast<float>(pos.x), static_cast<float>(pos.y), radius);
	nvgFill(context);

	selectBrush(oldBrush);
}

void Canvas::drawDot(int x, int y, NVGcolor color)
{
	Brush oldBrush = selectBrush(Brush(color));

	float radius = 1.0f;
	nvgCircle(context, static_cast<float>(x), static_cast<float>(y), radius);
	nvgFill(context);

	selectBrush(oldBrush);
}

void Canvas::drawLine(Vector2 from, Vector2 to)
{
	nvgBeginPath(context);
	nvgMoveTo(context, (int)from.x, (int)from.y);
	nvgLineTo(context, (int)to.x, (int)to.y);
}

void Canvas::drawLine(int a, int b, int x, int y)
{
	nvgBeginPath(context);
	nvgMoveTo(context, a, b);
	nvgLineTo(context, x, y);
}

void Canvas::drawLine(double a, double b, double x, double y)
{
	nvgBeginPath(context);
	nvgMoveTo(context, (int)a, (int)b);
	nvgLineTo(context, (int)x, (int)y);
}

void Canvas::drawPolyLine(const std::vector<Vector2>& points)
{
	// make sure we have at least 2 points
	if (points.size() < 2)
	{
		return;
	}

	nvgMoveTo(context, (int)points[0].x, (int)points[0].y);

	for (unsigned int p = 1; p < points.size(); ++p)
	{
		nvgLineTo(context, (int)points[p].x, (int)points[p].y);
	}
}

void Canvas::drawLineWithArrow(Vector2 from, Vector2 to, double size)
{
	Vector2 norm = Vector2::getNormalized(to - from);

	// calculate where the arrow is attached
	Vector2 crossingPoint = to - (norm * size);

	// calculate the two extra points required to make the arrowhead
	Vector2 arrowPoint1 = crossingPoint + (norm.getPerpendicular() * 0.4f * size);
	Vector2 arrowPoint2 = crossingPoint - (norm.getPerpendicular() * 0.4f * size);

	// draw the line
	nvgBeginPath(context);
	nvgMoveTo(context, (int)from.x, (int)from.y);
	nvgLineTo(context, (int)crossingPoint.x, (int)crossingPoint.y);

	// draw the arrowhead (filled with the currently selected brush)
	std::vector<Vector2> points;
	points.push_back(arrowPoint1);
	points.push_back(arrowPoint2);
	points.push_back(to);

	nvgPathWinding(context, NVG_SOLID);
	drawClosedShape(points);
}

void Canvas::drawCross(Vector2 pos, int diameter)
{
	drawLine((int)pos.x - diameter, (int)pos.y - diameter, (int)pos.x + diameter, (int)pos.y + diameter);
	drawLine((int)pos.x - diameter, (int)pos.y + diameter, (int)pos.x + diameter, (int)pos.y - diameter);
}

void Canvas::drawRect(int left, int top, int right, int bot)
{
	// depends on default y axis
	// windows: y axis grows from top to bottom
	// OGL: y axis grows from bottom to top
	float x = static_cast<float>(left);
	float y = static_cast<float>(top);
	float w = static_cast<float>(right - left);
	float h = static_cast<float>(bot - top);
	nvgRect(context, x, y, w, h);
	nvgFill(context);
	nvgStroke(context);
}

void Canvas::drawRect(double left, double top, double right, double bot)
{
	float x = static_cast<float>(left);
	float y = static_cast<float>(top);
	float w = static_cast<float>(right - left);
	float h = static_cast<float>(bot - top);
	nvgRect(context, x, y, w, h);
	nvgFill(context);
	nvgStroke(context);
}

void Canvas::drawClosedShape(const std::vector<Vector2>& points)
{
	nvgBeginPath(context);
	nvgMoveTo(context, (int)points[0].x, (int)points[0].y);

	for (unsigned int p = 1; p < points.size(); ++p)
	{
		nvgLineTo(context, (int)points[p].x, (int)points[p].y);
	}

	nvgLineTo(context, (int)points[0].x, (int)points[0].y);
	nvgFill(context);
	nvgStroke(context);
}

void Canvas::drawCircle(Vector2 pos, double radius)
{
	nvgBeginPath(context);
	nvgCircle(context, static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(radius));
}

void Canvas::drawCircle(double x, double y, double radius)
{
	nvgBeginPath(context);
	nvgCircle(context, static_cast<float>(x), static_cast<float>(y), static_cast<float>(radius));
}

void Canvas::drawCircle(int x, int y, double radius)
{
	nvgBeginPath(context);
	nvgCircle(context, static_cast<float>(x), static_cast<float>(y), static_cast<float>(radius));
}

void Canvas::setPenColor(int color)
{
	RIO_ASSERT(color < colorsCount, "");

	switch (color)
	{
	case black:		selectBlackPen(); return;
	case white:		selectWhitePen(); return;
	case red:		selectRedPen(); return;
	case green:		selectGreenPen(); return;
	case blue:		selectBluePen(); return;
	case pink:		selectPinkPen(); return;
	case grey:		selectGreyPen(); return;
	case yellow:	selectYellowPen(); return;
	case orange:	selectOrangePen(); return;
	case purple:	selectPurplePen(); return;
	case brown:		selectBrownPen(); return;
	case light_blue: selectLightBluePen(); return;
	case light_grey: selectLightGreyPen(); return;
	case light_pink: selectLightPinkPen(); return;
	}
}



