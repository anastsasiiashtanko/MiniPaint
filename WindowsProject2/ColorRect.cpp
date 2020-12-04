#include "stdafx.h"
#include "ColorRect.h"


ColorRect::ColorRect(int leftTopX, int  leftTopY, int rightBottomX, int rightBotomY, HBRUSH hbr, HPEN hp)
	:Rect(leftTopX, leftTopY, rightBottomX, rightBotomY),m_brush(hbr),m_pen(hp)
{
}


void ColorRect::draw(HDC hDC)
{
    HBRUSH oldBr = (HBRUSH)SelectObject(hDC, m_brush);
	HPEN oldPen = (HPEN)SelectObject(hDC, m_pen);
	Rectangle(hDC, m_leftTopX, m_leftTopY, m_rightBottomX, m_rightBotomY);
	HBRUSH newBr = (HBRUSH)SelectObject(hDC, oldBr);
	HPEN newPen = (HPEN)SelectObject(hDC, oldPen);
	//DeleteObject(newBr);
}
