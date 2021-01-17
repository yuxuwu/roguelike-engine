#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <wrl/client.h> // For ComPtr
#include "GameWindow.h"

struct DungeonMap {
	DungeonMap(std::vector<std::vector<char>> dungeonMap) {
		this->dungeonMap = dungeonMap;
	}
	std::vector<std::vector<char>> dungeonMap;
};
DungeonMap GenerateDungeonMapFromString(const std::string& levelfile_as_string)
{
	std::vector<std::vector<char>> dungeonMap;
	dungeonMap.emplace_back();
	for(int i = 0; i < levelfile_as_string.size(); ++i) {
		if(levelfile_as_string[i] == '\n') {
			dungeonMap.emplace_back();
		} else {
			dungeonMap.back().emplace_back(levelfile_as_string[i]);
		}
	}
	return DungeonMap(dungeonMap);
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



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR pCmdLine, int nCmdShow)
{
	GameWindow gameWindow;
	HWND hwnd = gameWindow.setupWindow(hInstance);

	//GameGraphics gameGraphics;
	//gameGraphics.setupGraphics();

	/*
	/// Get references to Direct3D Device and Context
	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_9_1,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_11_1
	};

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	D3D_FEATURE_LEVEL featureLevel;

	UINT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			deviceFlags,
			levels,
			ARRAYSIZE(levels),
			D3D11_SDK_VERSION,
			&device,
			&featureLevel,
			&context
			);

	if (FAILED(hr)) {
		std::cout << "Failed to create D3D11 Device" << std::endl;
		return -1;
	}

	/// Create Swap Chain
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.Windowed = TRUE;
	desc.BufferCount = 2;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	desc.OutputWindow = hwnd;

	Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
	Microsoft::WRL::ComPtr<IDXGIFactory> factory;

	hr = dxgiDevice->GetAdapter(&adapter);
	 */

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

			// Render during idle time (when no window messages are waiting)
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