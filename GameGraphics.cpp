//
// Created by Yu on 1/18/2021.
//
#ifndef UNICODE
#define UNICODE
#endif


#include "GameGraphics.h"
#include "utils/WindowsTest.h"

#include <windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <wrl/client.h>

#include <iostream>


void GameGraphics::setupGraphics(const HWND& hwnd) {
	_setupD3DDeviceAndContext();
	_setupD3DSwapChain(hwnd);
}

void GameGraphics::_setupD3DDeviceAndContext() {
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

	WindowsTest::debug(D3D11CreateDevice(
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
	));
}

void GameGraphics::_setupD3DSwapChain(const HWND& hwnd) {
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

	/*
	Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
	Microsoft::WRL::ComPtr<IDXGIFactory> factory;
	 */

	//hr = dxgiDevice->GetAdapter(&adapter);
}
