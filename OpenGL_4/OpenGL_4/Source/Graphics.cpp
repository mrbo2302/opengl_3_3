#include "Graphics.h"

Graphics::Graphics()
{
	m_ogl = NULL;
	m_spriteBatch = NULL;
}

Graphics::~Graphics()
{

}
//Function : Initialize Graphics
void Graphics::Initialize()
{
	m_spriteBatch = new SpriteBatch();
	m_spriteBatch->Initialize();
}
//Function : Initialize OpenGL and Extensions
bool Graphics::InitializeOGL(HWND pHWND)
{
	if (!m_ogl)
	{
		m_ogl = new OGL();
	}
	m_ogl->SetHWND(pHWND);
	if (!m_ogl->InitializeExtensions())
	{
		return false;
	}
	return true;

}

//Function : Begin Scene
void Graphics::BeginScene(float r, float b, float g, float a)
{
	m_ogl->BeginScene(r, b, g, a);
}

//Function: End Scene
void Graphics::EndScene()
{
	m_ogl->EndScene();
}

//Function : Get OpenGL class
OGL* Graphics::GetOpenGL()
{
	return m_ogl;
}

//Function : Get SpriteBatch
SpriteBatch* Graphics::GetSpriteBatch()
{
	return m_spriteBatch;
}

//Function : Release Memory
void Graphics::Release()
{
	if (m_ogl)
	{
		m_ogl->Release();
		delete m_ogl;
		m_ogl = NULL;
	}
	if (m_spriteBatch)
	{
		delete m_spriteBatch;
	}
}