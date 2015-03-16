#ifndef MATHCORE_H
#define MATHCORE_H

#define SIZE_ARRAY 4

class KMatrix4x4
{
public:
	KMatrix4x4();
	~KMatrix4x4();
	float Get(int row, int col);
	void Set(int row, int col,float value);
	void SetIdentity();

	float* AsArray();
	float m_matrix[SIZE_ARRAY][SIZE_ARRAY];
};

class Vector2
{
	float _x;
	float _y;
public:
	Vector2();
	Vector2(float x, float y);
	
};
class Vector3
{
	float _x;
	float _y;
	float _z;
public:
	Vector3();
	Vector3(float x, float y,float z);

};
#endif