#ifndef KRECTANGLE_H
#define KRECTANGLE_H
class KRectangle
{
	
public:
	//lazy to write get methods
	float _left;
	float _right;
	float _width;
	float _top;
	float _bottom;
	float _height;


	KRectangle();
	KRectangle(float left, float top, float width, float height);
	~KRectangle();
};

#endif