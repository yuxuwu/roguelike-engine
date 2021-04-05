#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <cstdio>

#pragma comment(lib, "d3d11.lib")

#include "GameWindow.h"
#include "GameGraphics.h"

#include <iostream>


static void CreateConsoleForOutput();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR pCmdLine, int nCmdShow)
{
	CreateConsoleForOutput();


	GameWindow gameWindow;
	gameWindow.registerAndCreateWindow(hInstance);
	HWND hwnd = gameWindow.getWindowHandler();

	GameGraphics gameGraphics;
	gameGraphics.setupGraphics(hwnd);

	gameGraphics.loadAndCompileTestShader();

	ShowWindow(hwnd, nCmdShow);

	/// Main Loop
	MSG msg;
	bool bGotMsg;
	msg.message = WM_NULL;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	while (WM_QUIT != msg.message)
	{
		// Process window events first
		// Use PeekMessage() so we can use idle time to render the scene.
		bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

		if (bGotMsg) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// Update the scene
			gameGraphics.renderFrame();
			// Render during idle time (when no window messages are waiting)
			//std::cout << "frame " << std::endl;
			// Present frame to screen
		}
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

void CreateConsoleForOutput() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); // redirect stdout to console
	HWND console_hwnd = GetConsoleWindow();
}
