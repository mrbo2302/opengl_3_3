#include "FrameWork.h"
#include "Engine.h"

LRESULT CALLBACK WndProc(HWND pHWND, UINT pMessage, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork()
{
	m_windowsTitle = "Test";
}
FrameWork::~FrameWork()
{
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	Engine::GetEngine()->Release();
	UnregisterClass(m_windowsTitle, m_hInstance);
	m_hInstance = NULL;
}

//Function : Initialize our FW
void FrameWork::Initialize()
{
	if (!CreateOpenGLWindows(m_windowsTitle, 0, 0, 1024, 768))
	{
		return;
	}
	Engine::GetEngine()->Initialize();
}

//Function : Run our Update and Render
void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	//Update Loop
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//update timer
			//run the engine
			Engine::GetEngine()->Run();
		}
	}
}

//Function : Create OpenGL Windows
bool FrameWork::CreateOpenGLWindows(char* pTitle, int x, int y, int width, int height)
{
	HWND hwnd;
	WNDCLASSEX wc;
	m_hInstance = GetModuleHandle(NULL);

	//setup the windows class with default settings
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = pTitle;
	wc.lpszMenuName = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Register Class Failed", "Error", MB_OK);
		return false;
	}

	//Create temporary windows for OpenGL extensions setup
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, pTitle, pTitle, WS_POPUP, 0, 0, 640, 480, NULL, NULL, m_hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Create WindowsEx Failed", "Error", MB_OK);
		return false;
	}

	//Dont show window
	ShowWindow(hwnd, SW_HIDE);

	Engine* engine = Engine::GetEngine();
	if (!engine->InitializeGraphics(hwnd))
	{
		MessageBox(hwnd, "Could not initialize the OpenGL Extensions", "Extreme Error", MB_OK);
		engine->Release();
		PostQuitMessage(0);
		DestroyWindow(hwnd);
		return false;
	}
	//Destroy the temporary window 
	DestroyWindow(hwnd);
	hwnd = NULL;

	//set window style
	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CXSCREEN);

	if (FULL_SCREEN)
	{
		DEVMODE dmScreenSetting;

		//fullscreen settings
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);
		dmScreenSetting.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSetting.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSetting.dmBitsPerPel = 32;
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//change it to full screen
		ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN);
	}
	else
	{
		screenWidth = width;
		screenHeight = height;
	}

	//Create our Window again
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, pTitle, pTitle, nStyle, x, y, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(hwnd, "Create Window Failed", "Extreme Error", MB_OK);
	}

	OGL* ogl = engine->GetGraphics()->GetOpenGL();
	ogl->SetHWND(hwnd);

	if (!ogl->InitializeOGL(VSYNC_ENABLE))
	{
		MessageBox(hwnd, "Create OGL Failed", "Extreme Error", MB_OK);
		engine->Release();
		PostQuitMessage(0);
		DestroyWindow(hwnd);
		return false;
	}
	//Show our window
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;

}

LRESULT CALLBACK WndProc(HWND pHWND, UINT pMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (pMessage)
	{
	case WM_KEYDOWN:
		if (wParam==VK_ESCAPE)
		{
			PostQuitMessage(0);
			DestroyWindow(pHWND);
		}
		break;
	case WM_KEYUP:
	{

	}
		break;
	case WM_PAINT:
	{
		hDC = BeginPaint(pHWND, &ps);
	}
		break;
	default:
		return DefWindowProc(pHWND, pMessage, wParam, lParam);
	}
	return 0;
}