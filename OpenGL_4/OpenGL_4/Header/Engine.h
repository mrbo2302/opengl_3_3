#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics.h"

class Engine
{
public:
	~Engine();

	//Function : Initialize the Graphics
	bool InitializeGraphics(HWND pHWND);

	//Function : Initialize Engine
	void Initialize();

	//Function : Update and Render for Engine
	void Run();

	//Function : Getter for graphics
	Graphics* GetGraphics();

	//Function : Release Memory
	void Release();

	//Function : Return the Singleton for the Engine
	static Engine* GetEngine();

private:
	static Engine* m_engine;
	Graphics* m_graphics;
};
#endif