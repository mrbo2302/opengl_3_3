#include "MathCore.h"
Vector2::Vector2()
{
	_x = 0.0f;
	_y = 0.0f;
}
Vector2::Vector2(float x, float y)
{
	_x = x;
	_y = y;
}

////////////////////////////////////////
/////////////Vector3///////////////////
//////////////////////////////////////
Vector3::Vector3()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}
Vector3::Vector3(float x, float y,float z)
{
	_x = x;
	_y = y;
	_z = z;
}