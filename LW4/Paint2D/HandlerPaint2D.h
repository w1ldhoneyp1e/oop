#pragma once
#include <ostream>
#include "ShapeStorage.h"
#include "ShapeProcessor.h"

class HandlerPaint2D
{
private:
	ShapeStorage m_storage;
	ShapeProcessor m_processor;
public:
	void HandleCommand(std::istream& input, std::ostream& output);

private:
	void HandleAddCircle(std::istringstream& iss, std::ostream& output);
	void HandleAddRectangle(std::istringstream& iss, std::ostream& output);
	void HandleAddTriangle(std::istringstream& iss, std::ostream& output);
	void HandleAddLine(std::istringstream& iss, std::ostream& output);
};

