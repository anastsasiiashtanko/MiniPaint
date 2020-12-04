#pragma once
#include "Shape.h"
class Rect :
	public Shape
{
public:
	Rect(int leftTopX,int leftTopY,int rightBottomX,int rightBotomY);
	~Rect()=default;
	virtual void draw(HDC hDC)override;
protected:
	int m_leftTopX;
	int m_leftTopY;
	int m_rightBottomX;
	int m_rightBotomY;
	int m_counter;
};