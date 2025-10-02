
#include <chrono>

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

	static inline VkInstance test_instance{};

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

using namespace std;
using namespace CorE;

int main()
{

	VkInstance test_instance_0;

	const char appname[] = "appname";
	uint32_t vers[4] = { 0, 1, 2, 3 };

	vec<const char*> extensions;
	extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	
	Application::initVulkan(appname, vers, 2, extensions.data());

	WNDCLASS wclass{};
	wclass.style = CS_HREDRAW | CS_VREDRAW;
	wclass.lpfnWndProc = DefWindowProc;
	wclass.cbClsExtra = 0;
	wclass.cbWndExtra = 0;
	wclass.hInstance = GetModuleHandle(NULL);
	wclass.lpszClassName = "TestWindowClass";

	Windowing::Window::Win32WindowCreateInfo w_create_info(
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		"Test window",
		CS_HREDRAW | CS_VREDRAW,
		"TestWindowClass"
	);

	Windowing::WindowProperties props{};
	props.width = 800;
	props.height = 600;
	Windowing::Window win(&props, &w_create_info);

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	return 0;
}
