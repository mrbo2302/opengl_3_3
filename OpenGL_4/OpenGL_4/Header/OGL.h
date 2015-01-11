#ifndef OGL_H
#define OGL_H

#include "glew.h"
#include "wglew.h"
////////////////////
////////DEFINES/////
////////////////////

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091

#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092

//typedefs that we need to access to the OpenGL 4.4 functionality

typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* atrribList);

class OGL
{
public :
	OGL();
	~OGL();
	//Function : Initialize OpenGL Extensions
	bool InitializeExtensions();

	//Function : Initialize OpenGL
	bool InitializeOGL(bool vSync);

	//Function : Begin the scene for OpenGL
	void BeginScene(float red, float blue, float green, float alpha);

	//Function : End the scene for OpenGL
	void EndScene();

	//Function : Gets name of GPU
	void GetVideoCardInfo(char* pInfo);

	//Function : Get HWND 
	HWND GetHWND();
	
	//Function : Set HWND
	void SetHWND(HWND pHWND);

	//Function : Release OpenGL;
	void Release();

private:
	//Function : Load Extensions
	bool LoadExtensions();

	HDC			m_deviceContext;
	HGLRC		m_renderContext;
	HWND		m_hwnd;
	PFNWGLCREATECONTEXTATTRIBSARBPROC	wglCreateContextAttribsARB;

	char		m_videoCardDesc[128];



};
#endif