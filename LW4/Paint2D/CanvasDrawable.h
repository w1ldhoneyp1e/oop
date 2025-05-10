#pragma once
#include "ICanvas.h"

class CanvasDrawable
{
public:
	virtual ~CanvasDrawable() = default;
	
	virtual void Draw(ICanvas& canvas) const = 0;
};

