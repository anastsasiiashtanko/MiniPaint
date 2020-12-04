#include "stdafx.h"
#include "ColorCircle.h"


ColorCircle::ColorCircle(int leftTopX, int  leftTopY, int rightBottomX, int rightBotomY, HBRUSH hbr,HPEN hp)
	:Circle(leftTopX, leftTopY, rightBottomX, rightBotomY), m_brush(hbr),m_pen(hp)
{
}


void ColorCircle::draw(HDC hDC)
{
	HBRUSH oldBr = (HBRUSH)SelectObject(hDC, m_brush);
	HPEN oldPen = (HPEN)SelectObject(hDC, m_pen);
	Ellipse(hDC, m_leftTopX, m_leftTopY, m_rightBottomX, m_rightBotomY);
	HBRUSH newBr = (HBRUSH)SelectObject(hDC, oldBr);
	HPEN newPen = (HPEN)SelectObject(hDC, oldPen);
	//DeleteObject(newBr);
}