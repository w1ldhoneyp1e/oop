#pragma once
#include "Point.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(Point from, Point to, std::uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<Point> points, std::uint32_t fillColor) = 0;
	virtual void DrawCircle(Point center, double radius, std::uint32_t lineColor) = 0;
	virtual void FillCircle(Point center, double radius, std::uint32_t fillColor) = 0;
	virtual void DrawRectangle(Point topLeft, double width, double height, std::uint32_t lineColor) = 0;
	virtual void FillRectangle(Point topLeft, double width, double height, std::uint32_t fillColor) = 0;
	virtual void DrawTriangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t lineColor) = 0;
	virtual void FillTriangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t fillColor) = 0;
};
