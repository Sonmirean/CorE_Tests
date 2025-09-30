#define CORENGINE_USE_PLATFORM_WIN32
#include "CorE/auxiliary/corengine.hpp"

#include "CorE/auxiliary/debug.hpp"
#include "CorE/engine/loop_manager.hpp"
#include "CorE/engine/windowing/window_manager.hpp"
#include "CorE/engine/core_manager.hpp"

using namespace std;


struct Herz : CorE::Heart
{
public:

	using Heart::Heart;

	void render()
	{
		cout << GetModuleHandle(NULL) << endl;
	}
};

LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


struct Win32Window
{
public:
	// Creates window procedure
	// Registers window class
	// Creates window
	Win32Window(DWORD window_style, LPCSTR window_name, DWORD class_style, LPCSTR class_name, int x, int y, int w, int h)
	{
		HINSTANCE hinstance = GetModuleHandle(NULL);

		WNDCLASS wclass{};
		wclass.style = class_style;
		wclass.lpfnWndProc = DefWindowProc;
		wclass.cbClsExtra = 0;
		wclass.cbWndExtra = 0;
		wclass.hInstance = GetModuleHandle(NULL);
		wclass.lpszClassName = class_name;
		ATOM res = RegisterClass(&wclass);
		if (!res)
		{
			throw;
		}
		hwnd = CreateWindow(class_name, window_name, window_style, x, y, w, h,
			nullptr, nullptr, hinstance, nullptr);
		if (!hwnd)
		{
			throw;
		}
		//ShowWindow(hwnd, 1);
	}
	~Win32Window()
	{
		DestroyWindow(hwnd);
	}

	HWND hwnd;
};



int main()
{

	const char appname[] = "appname";
	uint32_t vers[4] = { 0, 1, 2, 3 };

	CorE::Application::initVulkan(&appname[0], vers);

	CorE::math::Vec3 vec = { 1,2,3 };
	return 0;
}
