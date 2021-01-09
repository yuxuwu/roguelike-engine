#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>

class LevelMap {
private:
	std::vector<std::vector<char>> spaces;
public:
	LevelMap(std::string);
};

//std::vector<std::vector<char>> GenerateSpacesFilename(const std::string& fileName)
std::vector<std::vector<char>> GenerateSpacesFromLevelFilename(const std::string& levelFilename)
{
	return {{}};
}

std::string importFileToString(std::string filename) {
	std::string result;
	std::ifstream fileStream(filename);

	if(fileStream.is_open()){
		result = std::string(
				(std::istreambuf_iterator<char>(fileStream)),
				(std::istreambuf_iterator<char>()));
		fileStream.close();
	}

	return result;
}

LevelMap::LevelMap(std::string levelFilename){
	/// Readfile into level
	this->spaces = GenerateSpacesFromLevelFilename(levelFilename);
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR pCmdLine, int nCmdShow)
{
	/// Register the window class.
	const wchar_t CLASS_NAME[]  = L"Sample Window Class";

	WNDCLASS wc = { };
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.
	HWND hwnd = CreateWindowEx(
			0,                              // Optional window styles.
			CLASS_NAME,                     // Window class
			L"Learn to Program Windows",    // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window
			NULL,       // Menu
			hInstance,  // Instance handle
			NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	// Run the message loop.
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

			EndPaint(hwnd, &ps);
		}
			return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}