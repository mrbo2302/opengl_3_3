#include "KRectangle.h"
KRectangle::KRectangle()
{
	_left = 0.0f;
	_right = 0.0f;
	_width = 0.0f;
	_top = 0.0f;
	_bottom = 0.0f;
	_height = 0.0f;
}
KRectangle::KRectangle(float left, float top, float width, float height)
{
	_left = left;
	_right = left + width;
	_width = width;
	_top = top;
	_bottom = top + height;
	_height = height;
}
KRectangle::~KRectangle()
{

}