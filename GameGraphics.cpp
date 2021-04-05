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
	_setupViewport(nullptr);
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
					nullptr,                  //Pointer to: Video Adapter, null being default adapter
					D3D_DRIVER_TYPE_HARDWARE, //Driver Type
					0,                        //Software Rasterizer
					deviceFlags,              //Flags
					_levels,                  //Feature levels
					ARRAYSIZE(_levels),       //Number Feature Levels given
					D3D11_SDK_VERSION,        //SDK Version
					&swapChainDesc,           //Pointer to: Swap Chain Desc
					&(_d3dSwapChain),         //Pointer to Output: Swap Chain
					&(_d3dDevice),            //Pointer to Output: D3D Device
					&(_d3dFeatureLevel),      //Pointer to Output: Determined Feature Level
					&(_d3dContext)            //Pointer to Output: D3D Device Context
			)
	);
}

void GameGraphics::_setupRenderTargets() {
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	_d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.ReleaseAndGetAddressOf()));
	_d3dDevice->CreateRenderTargetView(backBuffer.Get(), NULL, _backBuffer.ReleaseAndGetAddressOf());
	_d3dContext->OMSetRenderTargets(1, _backBuffer.GetAddressOf(), NULL);
}

void GameGraphics::_setupViewport(const HWND &hwnd) {
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	_d3dContext->RSSetViewports(1, &viewport);
}

/// Vertices Part
struct VERTEX {
	float X, Y, Z; // Vertex Position
};
Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

void GameGraphics::renderFrame() {
	_d3dContext->OMSetRenderTargets(1, _backBuffer.GetAddressOf(), nullptr);
	_clearRenderingTarget();
	// Vertex Buffer
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	_d3dContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_d3dContext->Draw(3, 0);

	_d3dSwapChain->Present(1, 0);
}

void GameGraphics::_clearRenderingTarget() {
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	_d3dContext->ClearRenderTargetView(_backBuffer.Get(), color);
}

void GameGraphics::loadAndCompileTestShader() {


	// Shaders Part
	Shader vertShader = Shader(L"testfiles/shaders.shader", "VShader", Shader::Type::Vertex);
	Shader pixShader = Shader(L"testfiles/shaders.shader", "PShader", Shader::Type::Pixel);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> VS;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PS;

	DEBUG_HR(_d3dDevice->CreateVertexShader(
			vertShader.getCompileResult().compiledShaderBlob->GetBufferPointer(),
			vertShader.getCompileResult().compiledShaderBlob->GetBufferSize(),
			nullptr,
			VS.GetAddressOf()
	));
	DEBUG_HR(_d3dDevice->CreatePixelShader(
			pixShader.getCompileResult().compiledShaderBlob->GetBufferPointer(),
			pixShader.getCompileResult().compiledShaderBlob->GetBufferSize(),
			nullptr,
			PS.GetAddressOf()
	));
	if(vertShader.getCompileResult().status == Shader::ShaderCompileResult::Status::FAILURE) {
		std::cout << vertShader.getCompileResult().message << std::endl;
	}
	if(pixShader.getCompileResult().status == Shader::ShaderCompileResult::Status::FAILURE) {
		std::cout << pixShader.getCompileResult().message << std::endl;
	}
	_d3dContext->VSSetShader(VS.Get(), 0, 0);

	_d3dContext->PSSetShader(PS.Get(), 0, 0);

	/// Vertex Input Layout
	// Input Element One: Position
	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	DEBUG_HR(_d3dDevice->CreateInputLayout(
			ied,
			ARRAYSIZE(ied),
			vertShader.getCompileResult().compiledShaderBlob->GetBufferPointer(),
			vertShader.getCompileResult().compiledShaderBlob->GetBufferSize(),
			&inputLayout
	));
	_d3dContext->IASetInputLayout(inputLayout.Get());


	VERTEX OurVertices[] = {
			{0.0f, 0.5f, 0.0f},
			{0.45f, -0.5f, 0.0f},
			{-0.45f, -0.5f, 0.0f}
	};

	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA srd = {OurVertices, 0, 0};
	DEBUG_HR(_d3dDevice->CreateBuffer(&bd, &srd, &vertexBuffer));


}
