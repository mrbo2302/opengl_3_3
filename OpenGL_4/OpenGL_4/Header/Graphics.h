#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "OGL.h"
static bool FULL_SCREEN = false;
static bool VSYNC_ENABLE = true;
class Graphics
{
public:
	Graphics();
	~Graphics();

	//Function : Initialize OpenGL and Extensions
	bool InitializeOGL(HWND pHWND);

	//Function : Begin Scene
	void BeginScene(float r, float b, float g, float a);

	//Function: End Scene
	void EndScene();

	//Function : Get OpenGL class
	OGL* GetOpenGL();

	//Function : Release Memory
	void Release();


private:
	OGL* m_ogl;
};
#endif