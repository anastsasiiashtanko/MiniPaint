#include "stdafx.h"
#include "Rect.h"


Rect::Rect(int leftTopX, int leftTopY, int rightBottomX, int rightBotomY)
	:m_leftTopX(leftTopX),m_leftTopY(leftTopY),m_rightBottomX(rightBottomX),m_rightBotomY(rightBotomY)
{

}



void Rect::draw(HDC hDC)
{
	Rectangle(hDC, m_leftTopX, m_leftTopY, m_rightBottomX, m_rightBotomY);
	++m_counter;
}