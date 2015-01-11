#include "OGL.h"

#include <iostream>
using namespace std;

OGL::OGL()
{
	m_deviceContext = 0;
	m_renderContext = 0;

}
OGL::~OGL()
{

}

//Function : Initialize OpenGL
bool OGL::InitializeOGL(bool vSync)
{
	cout<< "initialize OpenGL" << endl;

	//int attributeListInt[19];
	int pixelFormat;
	int result = 0;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int attributeList[5];
	char* vendorChar, *rendererChar;

	//get device
	m_deviceContext = GetDC(m_hwnd);
	if (!m_deviceContext)
	{
		return false;
	}

	//set OpenGL rendering
	
	//Query for a pixel format that will get the attribute that we want
	pixelFormat = ChoosePixelFormat(m_deviceContext,&pixelFormatDescriptor);
	if (pixelFormat == 0)
	{
		return false;
	}

	//if the video card can handle our desired pixel format
	result = SetPixelFormat(m_deviceContext, pixelFormat, &pixelFormatDescriptor);
	if (result != 1)
	{
		return false;
	}

	//make temporary context that will initialize our opengl wrangler
	HGLRC tempOpenGLContext = wglCreateContext(m_deviceContext); //create OpenGL 2.1
	wglMakeCurrent(m_deviceContext, tempOpenGLContext);

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	//Set the 4.0 version of OpenGL

	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;
	attributeList[4] = 0;

	//create an OpenGL 4.0 render context
	m_renderContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributeList);

	if (m_renderContext != NULL)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempOpenGLContext);

		//set the render context to 4.0
		result = wglMakeCurrent(m_deviceContext, m_renderContext);
		if (result != 1)
		{
			return false;
		}
	}

	vendorChar = (char*)glGetString(GL_VENDOR);
	rendererChar = (char*)glGetString(GL_RENDERER);

	//store information of our gfx card
	strcpy_s(m_videoCardDesc, vendorChar);
	strcat_s(m_videoCardDesc, "-");
	strcat_s(m_videoCardDesc, rendererChar);

	if (vSync)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	//make vsync is set correctly
	if (result != 1)
	{
		return false;
	}

	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[2]);

	cout << "Intializing OpenGL SUCCESS" << endl;
	cout << "Using OpenGL 4.0" << glVersion[0] <<  "." << glVersion[1] << endl;
	cout << "GPU :" << m_videoCardDesc << endl;
	return true;

}

//Function : Initialize Extension
bool OGL::InitializeExtensions()
{
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = 0;

	HGLRC renderContext;
	bool result = false;

	//get the device context for this window
	deviceContext = GetDC(m_hwnd);
	if (!deviceContext)
	{
		return false;
	}

	//set temporary default pixel format
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}
	
	//create render context
	renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}

	//set temporary render context as the current render context for this window
	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	//initialize extensions
	result = LoadExtensions();
	if (!result)
	{
		return false;
	}

	//release
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;
	ReleaseDC(m_hwnd, deviceContext);
	deviceContext = 0;

	return true;

}

//Function : Load Extension
bool OGL::LoadExtensions()
{
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttibsARB");
	if (!wglCreateContextAttribsARB)
	{
		return false;
	}
	return true;
}

//Function : Begin Scene for OpenGL
void OGL::BeginScene(float r, float b, float g, float a)
{
	glClearColor(r, b, g, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Function : End Scene for OpenGL
void OGL::EndScene()
{
	glFlush();
	SwapBuffers(m_deviceContext);
	glFinish();
}

//Function : Release OpenGL
void OGL::Release()
{
	if (m_renderContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderContext);
		m_renderContext = 0;
	}
	if (m_deviceContext)
	{
		ReleaseDC(m_hwnd, m_deviceContext);
		m_deviceContext = 0;
	}
}

