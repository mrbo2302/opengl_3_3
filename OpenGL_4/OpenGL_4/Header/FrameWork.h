#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define WIN32_LEAN_AND_MEAN
#include "OGL.h"
class FrameWork
{
public:
	FrameWork();
	~FrameWork();

	//Function : Initialize our FW
	void Initialize();

	//Function : Run our Update and Render
	void Run();
private:
	//Function : Create OpenGL Windows
	bool CreateOpenGLWindows(char* pTitle, int x, int y, int width, int height);
	HINSTANCE m_hInstance;
	char* m_windowsTitle;
};

#endif