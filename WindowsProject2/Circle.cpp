#include "stdafx.h"
#include "Circle.h"


Circle::Circle(int leftTopX, int leftTopY, int rightBottomX, int rightBotomY)
	:m_leftTopX(leftTopX), m_leftTopY(leftTopY), m_rightBottomX(rightBottomX), m_rightBotomY(rightBotomY)
{
}



void Circle::draw(HDC hDC)
{
	Ellipse(hDC, m_leftTopX, m_leftTopY, m_rightBottomX, m_rightBotomY);
	++m_counter;
}