#pragma once
#include <ostream>
#include <functional>
#include <map>
#include <string>
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
	
	using CommandHandler = std::function<void(std::istringstream&, std::ostream&)>;
	std::map<std::string, CommandHandler> m_commandHandlers;

	void HandleAddCircle(std::istringstream& iss, std::ostream& output);
	void HandleAddRectangle(std::istringstream& iss, std::ostream& output);
	void HandleAddTriangle(std::istringstream& iss, std::ostream& output);
	void HandleAddLine(std::istringstream& iss, std::ostream& output);
	void HandleBiggestArea(std::istringstream& iss, std::ostream& output);
	void HandleSmallestPerimeter(std::istringstream& iss, std::ostream& output);
	void HandleClear(std::istringstream& iss, std::ostream& output);
};

