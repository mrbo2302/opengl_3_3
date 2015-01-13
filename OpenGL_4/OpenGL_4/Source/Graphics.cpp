#include "Graphics.h"

Graphics::Graphics()
{
	m_ogl = NULL;
}

Graphics::~Graphics()
{

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

//Function : Release Memory
void Graphics::Release()
{
	if (m_ogl)
	{
		m_ogl->Release();
		delete m_ogl;
		m_ogl = NULL;
	}
}