#pragma once
#include "Circle.h"
class ColorCircle :
	public Circle
{
public:
	ColorCircle(int leftTopX, int  leftTopY, int rightBottomX, int rightBotomY, HBRUSH hbr,HPEN hp);
	virtual ~ColorCircle() = default;
	virtual void draw(HDC hDC)override;
private:
	HBRUSH m_brush;
	HPEN m_pen;
};

