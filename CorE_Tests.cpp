
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
	const char* appref = &appname[0];

	VkAllocationCallbacks* kabaks = nullptr;

	 
	/// try to manually create valid instance info
	const VkApplicationInfo const_application_info
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = &appname[0],
		.applicationVersion = VK_MAKE_API_VERSION(vers[0], vers[1], vers[2], vers[3]),
		.pEngineName = "CorEngine",
		.engineVersion = VK_MAKE_API_VERSION(CORENGINE_VERSION_MAJOR, CORENGINE_VERSION_MINOR, CORENGINE_VERSION_PATCH, CORENGINE_VERSION_BUILD),
		.apiVersion = VK_API_VERSION_1_0
	};

	VkApplicationInfo test_application_info;
	test_application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	test_application_info.pApplicationName = &appname[0];
	test_application_info.applicationVersion = VK_MAKE_API_VERSION(vers[0], vers[1], vers[2], vers[3]);
	test_application_info.pEngineName = "CorEngine";
	test_application_info.engineVersion = VK_MAKE_API_VERSION(CORENGINE_VERSION_MAJOR, CORENGINE_VERSION_MINOR, CORENGINE_VERSION_PATCH, CORENGINE_VERSION_BUILD),
	test_application_info.apiVersion = VK_API_VERSION_1_0;
	

	VkInstanceCreateInfo test_instance_create_info;
	test_instance_create_info.enabledExtensionCount = 0;
	test_instance_create_info.enabledLayerCount = 0;
	test_instance_create_info.flags = 0;
	test_instance_create_info.pApplicationInfo = &TESTS::testAppInfoCreation(&appname[0], vers);
	test_instance_create_info.pNext = nullptr;
	test_instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	test_instance_create_info.ppEnabledLayerNames = nullptr;
	test_instance_create_info.ppEnabledExtensionNames = nullptr;
	
	ensureVkSuccess(vkCreateInstance(&test_instance_create_info, nullptr, &test_instance_0));
	// YES! It works. ^^^
	///
//

/// the issue is something to deal with const operator.
	/// But I'm not sure

	VkInstanceCreateInfo info = TESTS::testInstanceInfoCreation(&test_application_info);

	bool _0 = info.enabledExtensionCount == test_instance_create_info.enabledExtensionCount;
	bool _1 = info.enabledLayerCount == test_instance_create_info.enabledLayerCount;
	bool _2 = info.flags == test_instance_create_info.flags;
	bool _3 = info.pApplicationInfo == test_instance_create_info.pApplicationInfo;
	bool _4 = info.pNext == test_instance_create_info.pNext;///////
	bool _5 = info.ppEnabledExtensionNames == test_instance_create_info.ppEnabledExtensionNames;
	bool _6 = info.ppEnabledLayerNames == test_instance_create_info.ppEnabledLayerNames;
	bool _7 = info.sType == test_instance_create_info.sType;

	cout << _0 << "\n"
		<< _1 << "\n"
		<< _2 << "\n"
		<< _3 << "\n"
		<< _4 << "\n"
		<< _5 << "\n"
		<< _6 << "\n"
		<< _7 << "\n \n \n";

	cout << info.pNext << "\n"
		<< test_instance_create_info.pNext << "\n \n \n";
	// nullptr != nullptr

	printf("instance info ptrs\n");
	cout << &info << "\n"
		<< &test_instance_create_info << "\n \n \n";
	/// just normal pointers

	// vvv fails vvv
	ensureVkSuccess(vkCreateInstance(&TESTS::testInstanceInfoCreation(&test_application_info), nullptr, &test_instance_0));
	


	int* pa = nullptr;
	bool* pb = nullptr;
	VkInstance* pc = nullptr;

	cout << &Application::instance << "\n";
	Application::instance = nullptr;
	cout << &Application::instance << "\n";
	cout << nullptr << "\n";
	cout << pa << "\n";
	cout << pb << "\n";
	cout << pc << "\n";
	cout << &Herz::test_instance << "\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	return 0;
}
