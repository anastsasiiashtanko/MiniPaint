#pragma once
class Shape
{
public:
	Shape()=default;
	virtual ~Shape()=default;
	virtual void draw(HDC hDC)=0;
};

