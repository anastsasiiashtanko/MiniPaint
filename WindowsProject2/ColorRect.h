#pragma once
#include "Rect.h"
#include <Windows.h>
class ColorRect :
	public Rect
{
public:
	ColorRect(int leftTopX, int  leftTopY, int rightBottomX, int rightBotomY, HBRUSH hbr, HPEN hp);
	virtual ~ColorRect() = default;
	virtual void draw(HDC hDC)override;
private:
	HBRUSH m_brush;
	HPEN m_pen;
};

