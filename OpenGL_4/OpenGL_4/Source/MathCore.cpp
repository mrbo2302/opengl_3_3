#include "MathCore.h"
#include <assert.h>
#include <memory.h>

////////////////////////////////////////
/////////////Matrix 4x4////////////////
//////////////////////////////////////
KMatrix4x4::KMatrix4x4()
{
	SetIdentity();
}
KMatrix4x4::~KMatrix4x4()
{

}
void KMatrix4x4::Set(int row, int col,float value)
{
	assert(row >= 0 && row < SIZE_ARRAY);
	assert(col >= 0 && col < SIZE_ARRAY);
	this->m_matrix[row][col] = value;
}
float KMatrix4x4::Get(int row, int col)
{
	assert(row >= 0 && row < SIZE_ARRAY);
	assert(col >= 0 && col < SIZE_ARRAY);
	return this->m_matrix[row][col];
}
void KMatrix4x4::SetIdentity()
{
	memset(&this->m_matrix, 0, sizeof(float)*SIZE_ARRAY*SIZE_ARRAY);
	this->m_matrix[0][0] = 1.0f;
	this->m_matrix[1][1] = 1.0f;
	this->m_matrix[2][2] = 1.0f;
	this->m_matrix[3][3] = 1.0f;
}

float* KMatrix4x4::AsArray()
{
	return (float*)this->m_matrix;
}


////////////////////////////////////////
/////////////Vector2///////////////////
//////////////////////////////////////
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
float Vector2::GetX()
{
	return _x;
}
float Vector2::GetY()
{
	return _y;
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
float Vector3::GetX()
{
	return _x;
}
float Vector3::GetY()
{
	return _y;
}
float Vector3::GetZ()
{
	return _z;
}