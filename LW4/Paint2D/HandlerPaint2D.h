#pragma once
#include <ostream>
#include "ShapeStorage.h"
#include "ShapeProcessor.h"

class HandlerPaint2D
{
public:
	HandlerPaint2D(ShapeStorage& storage, ShapeProcessor& processor);

	void HandleCommand(std::string& command, std::ostream& output);

private:
	ShapeStorage& m_storage;
	ShapeProcessor& m_processor;

	void HandleAddCircle(std::istringstream& iss, std::ostream& output);
	void HandleAddRectangle(std::istringstream& iss, std::ostream& output);
	void HandleAddTriangle(std::istringstream& iss, std::ostream& output);
	void HandleAddLine(std::istringstream& iss, std::ostream& output);
	bool IsValidColor(const std::string& colorStr);
};

