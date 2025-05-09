#pragma once
#include <ostream>
#include "ShapeStorage.h"
#include "ShapeProcessor.h"
#include "Canvas.h"

class HandlerPaint2D
{
public:
	HandlerPaint2D(ShapeStorage& storage, ShapeProcessor& processor, Canvas& canvas);

	void HandleCommand(std::istream& input, std::ostream& output);

private:
	ShapeStorage& m_storage;
	ShapeProcessor& m_processor;
	Canvas& m_canvas;

	void HandleAddCircle(std::istringstream& iss, std::ostream& output);
	void HandleAddRectangle(std::istringstream& iss, std::ostream& output);
	void HandleAddTriangle(std::istringstream& iss, std::ostream& output);
	void HandleAddLine(std::istringstream& iss, std::ostream& output);
};

