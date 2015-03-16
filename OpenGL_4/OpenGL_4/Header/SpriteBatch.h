#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "MathCore.h"
#include "SystemDefs.h"
#include "KRectangle.h"
class SpriteBatch
{
	U32 m_vertexBufferID;
	U32 m_texBufferID;
	U32 m_indexBufferID;
	U32 m_vertexArrayID;

	int m_indicesCount;

public:
	SpriteBatch();
	~SpriteBatch();

	//Function : Initialize SpriteBatch
	void Initialize();

	//Function : Draw a 2D plan
	void Draw(KRectangle& pRect);

};
#endif