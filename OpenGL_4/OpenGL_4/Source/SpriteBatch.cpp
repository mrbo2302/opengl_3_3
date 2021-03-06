#include "SpriteBatch.h"
#include "OGL.h"
SpriteBatch::SpriteBatch()
{
	m_vertexBufferID = 0;
	m_texBufferID = 0;
	m_indexBufferID = 0;
	m_vertexArrayID = 0;
}
SpriteBatch::~SpriteBatch()
{
	if (m_vertexBufferID)
	{
		glDeleteBuffers(1, &m_vertexBufferID);
	}
	if (m_texBufferID)
	{
		glDeleteBuffers(1, &m_texBufferID);
	}
	if (m_indexBufferID)
	{
		glDeleteBuffers(1, &m_indexBufferID);
	}
	if (m_vertexArrayID)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_vertexArrayID);
	}
}
//Function : Initialize SpriteBatch
void SpriteBatch::Initialize()
{
	glGenVertexArrays(1, &m_vertexArrayID);
	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_texBufferID);
	glGenBuffers(1, &m_indexBufferID);

}

//Function : Draw a 2D plan
void SpriteBatch::Draw(KRectangle& pRect)
{
	Vector3 verts[4];
	Vector2 uv[4];
	U32 indicies[6];
	m_indicesCount = 6;

	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 1;
	indicies[4] = 2;
	indicies[5] = 3;

	float left = pRect._left - (pRect._width / 2.0f);
	float right = left + pRect._width;
	float top = pRect._top - (pRect._height / 2.0f);
	float bot = top + pRect._height;

	verts[0] = Vector3(left, top, 0.0f);
	uv[0] = Vector2(0.0f, 0.0f);

	verts[1] = Vector3(right, top, 0.0f);
	uv[1] = Vector2(1.0f, 0.0f);

	verts[2] = Vector3(left, bot, 0.0f);
	uv[2] = Vector2(0.0f, 1.0f);

	verts[3] = Vector3(right, bot, 0.0f);
	uv[3] = Vector2(1.0f, 1.0f);

	glBindVertexArray(m_vertexArrayID);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vector3),0);


	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), uv, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount*sizeof(U32), indicies, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}