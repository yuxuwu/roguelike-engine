//
// Created by Yu on 1/18/2021.
//
#ifndef UNICODE
#define UNICODE
#endif

#include "GameGraphics.h"
#include "error_handling/WindowsErrorHandling.h"
#include "graphics/Shader.h"

#include <windows.h>

#include <iostream>



void GameGraphics::setupGraphics(const HWND& hwnd) {
	_setupD3DDeviceAndSwapChain(hwnd);
	_setupRenderTargets();
	_setupViewport();
}

void GameGraphics::_setupD3DDeviceAndSwapChain(const HWND &hwnd) {
	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.OutputWindow = hwnd;

	DEBUG_HR(
			//OPT: Creating device and swap chain recreates device resources
			//     for the swap chain, more efficient to create separately from
			//     device itself.
			D3D11CreateDeviceAndSwapChain(
					nullptr,
					D3D_DRIVER_TYPE_HARDWARE,
					0,
					deviceFlags,
					_levels,
					ARRAYSIZE(_levels),
					D3D11_SDK_VERSION,
					&swapChainDesc,
					&(_d3dSwapChain),
					&(_d3dDevice),
					&(_d3dFeatureLevel),
					&(_d3dContext)
			)
	);
}

void GameGraphics::_setupRenderTargets() {
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	_d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.ReleaseAndGetAddressOf()));
	_d3dDevice->CreateRenderTargetView(backBuffer.Get(), NULL, _backBuffer.ReleaseAndGetAddressOf());
	_d3dContext->OMSetRenderTargets(1, _backBuffer.GetAddressOf(), NULL);
}

void GameGraphics::_setupViewport() {
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	_d3dContext->RSSetViewports(1, &viewport);
}

void GameGraphics::renderFrame() {
	_clearRenderingTarget();

	_d3dSwapChain->Present(0, 0);
}

void GameGraphics::_clearRenderingTarget() {
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	_d3dContext->ClearRenderTargetView(_backBuffer.Get(), color);

}



void GameGraphics::loadAndCompileTestShader() {
	Shader vertShader = Shader(L"testfiles/shaders.shader", "VShader", Shader::Type::Vertex);
	Shader pixShader = Shader(L"testfiles/shaders.shader", "PShader", Shader::Type::Pixel);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> VS;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PS;


	/*
	_d3dDevice->CreateVertexShader(
		VS->GetBufferPointer(),
		VS->GetBufferSize(),
		NULL,
		VS.GetAddressOf()
	);
	 _d3dDevice->CreatePixelShader(
		PS->GetBufferPointer(),
		PS->GetBufferSize(),
		NULL,
		pPS.GetAddressOf()
	);

	_d3dContext->VSSetShader(pVS.Get(), 0, 0);
	_d3dContext->PSSetShader(pPS.Get(), 0, 0);
	 */
}
