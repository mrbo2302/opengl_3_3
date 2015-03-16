#include "Engine.h"

Engine* Engine::m_engine = NULL;

Engine::~Engine()
{
	m_graphics = NULL;

}

//Function : Initialize the Graphics
bool Engine::InitializeGraphics(HWND pHWND)
{
	m_graphics = new Graphics();
	return m_graphics->InitializeOGL(pHWND);
}

//Function : Initialize Engine
void Engine::Initialize()
{
	m_graphics->Initialize();
}

//Function : Update and Render for Engine
void Engine::Run()
{
	m_graphics->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//render our scene


	m_graphics->EndScene();


}

//Function : Getter for graphics
Graphics* Engine::GetGraphics()
{
	return m_graphics;
}

//Function : Release Memory
void Engine::Release()
{
	if (m_graphics)
	{
		m_graphics->Release();
		delete m_graphics;
		m_graphics = NULL;
	}
	if (m_engine)
	{
		delete m_engine;
		m_engine = NULL;
	}

}

//Function : Return the Singleton for the Engine
Engine* Engine::GetEngine()
{
	if (!m_engine)
	{
		m_engine = new Engine();
	}
	return m_engine;
}