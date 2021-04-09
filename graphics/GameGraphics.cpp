//
// Created by Yu on 1/18/2021.
//
#ifndef UNICODE
#define UNICODE
#endif

#include "GameGraphics.h"
#include "../error_handling/WindowsErrorHandling.h"

void GameGraphics::Init(const HWND& hwnd) {
	setupD3DDeviceAndSwapChain(hwnd);
	setupRenderTargets();
	setupViewport(hwnd);
}

static std::string ParseStringFromErrorBlob(ID3DBlob *errorBlob) {
	return (char*)errorBlob->GetBufferPointer();
}

static std::string CreateShaderCompileMessage(ID3DBlob* compileErrors) {
	std::string result{};

	if(compileErrors) {
		result = "A compile error was found for the shader: " +
				 ParseStringFromErrorBlob(compileErrors);
		compileErrors->Release();
	}
	return result;
}


VertexShaderCreateResult GameGraphics::CreateVertexShader(const std::wstring& filepath, const std::string& entrypoint) {

	VertexShaderCreateResult result;

	ID3DBlob *compileErrors = nullptr;
	DEBUG_HR(
			D3DCompileFromFile(
					filepath.c_str(),                                 // filename
					nullptr,                                          // define shader macros (optional)
					nullptr,                                          // shader include files (optional)
					entrypoint.c_str(),                               // shader entry point function
					"vs_4_0", // compilation target
					0,                                                // compile options bitfield (optional)
					0,                                                // compile options 2 bitfield (optional)
					&result.compile_result.compiledShaderBlob,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);

	result.compile_result.message = CreateShaderCompileMessage(compileErrors);


	DEBUG_HR(d3dDevice->CreateVertexShader(
			result.compile_result.compiledShaderBlob->GetBufferPointer(),
			result.compile_result.compiledShaderBlob->GetBufferSize(),
			nullptr,
			result.shader_object.GetAddressOf()
	));

	if(!result.compile_result.message.empty())
		std::cout << "SHADER COMPILE ERROR: " << result.compile_result.message << std::endl;

	return result;
}



PixelShaderCreateResult GameGraphics::CreatePixelShader(const std::wstring& filepath, const std::string& entrypoint) {

	PixelShaderCreateResult result;

	ID3DBlob *compileErrors = nullptr;
	DEBUG_HR(
			D3DCompileFromFile(
					filepath.c_str(),                                 // filename
					nullptr,                                          // define shader macros (optional)
					nullptr,                                          // shader include files (optional)
					entrypoint.c_str(),                               // shader entry point function
					"ps_4_0", // compilation target
					0,                                                // compile options bitfield (optional)
					0,                                                // compile options 2 bitfield (optional)
					&result.compile_result.compiledShaderBlob,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);

	result.compile_result.message = CreateShaderCompileMessage(compileErrors);

	DEBUG_HR(d3dDevice->CreatePixelShader(
			result.compile_result.compiledShaderBlob->GetBufferPointer(),
			result.compile_result.compiledShaderBlob->GetBufferSize(),
			nullptr,
			result.shader_object.GetAddressOf()
	));

	if(!result.compile_result.message.empty())
		std::cout << "SHADER COMPILE ERROR: " << result.compile_result.message << std::endl;

	return result;
}

void GameGraphics::setupD3DDeviceAndSwapChain(const HWND &hwnd) {
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
					D3D_DRIVER_TYPE_HARDWARE, //Driver ShaderType
					0,                        //Software Rasterizer
					deviceFlags,              //Flags
					_levels,                  //Feature levels
					ARRAYSIZE(_levels),       //Number Feature Levels given
					D3D11_SDK_VERSION,        //SDK Version
					&swapChainDesc,           //Pointer to: Swap Chain Desc
					&(d3dSwapChain),         //Pointer to Output: Swap Chain
					&(d3dDevice),            //Pointer to Output: D3D Device
					&(d3dFeatureLevel),      //Pointer to Output: Determined Feature Level
					&(d3dContext)            //Pointer to Output: D3D Device Context
			)
	);
}

void GameGraphics::setupRenderTargets() {
	Microsoft::WRL::ComPtr<ID3D11Resource> currentBackBuffer;

	d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(currentBackBuffer.ReleaseAndGetAddressOf()));
	d3dDevice->CreateRenderTargetView(currentBackBuffer.Get(), NULL, backBuffer.ReleaseAndGetAddressOf());
	d3dContext->OMSetRenderTargets(1, backBuffer.GetAddressOf(), NULL);
}

void GameGraphics::setupViewport(const HWND &hwnd) {
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	RECT rect{};
	GetWindowRect(hwnd, &rect);

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = rect.right - rect.left;
	viewport.Height = rect.bottom - rect.top;

	std::cout << "Width: " << viewport.Width << " Height: " << viewport.Height << std::endl;

	d3dContext->RSSetViewports(1, &viewport);
}

/// Vertices Part
struct VERTEX {
	float X, Y, Z; // Vertex Position
};
Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

void GameGraphics::renderFrame() {
	d3dContext->OMSetRenderTargets(1, backBuffer.GetAddressOf(), nullptr);
	clearRenderingTarget();
	// Vertex Buffer
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	d3dContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dContext->Draw(3, 0);

	d3dSwapChain->Present(1, 0);
}

void GameGraphics::clearRenderingTarget() {
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	d3dContext->ClearRenderTargetView(backBuffer.Get(), color);
}

void GameGraphics::loadAndCompileTestShader() {

	VertexShaderCreateResult vertShader = CreateVertexShader(L"testfiles/shaders.shader", "VShader");
	PixelShaderCreateResult pixShader = CreatePixelShader(L"testfiles/shaders.shader", "PShader");


	d3dContext->VSSetShader(vertShader.shader_object.Get(), 0, 0);

	d3dContext->PSSetShader(pixShader.shader_object.Get(), 0, 0);

	VERTEX OurVertices[] = {
			{0.0f, 0.5f, 0.0f},
			{0.45f, -0.5f, 0.0f},
			{-0.45f, -0.5f, 0.0f}
	};

	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA srd = {OurVertices, 0, 0};
	DEBUG_HR(d3dDevice->CreateBuffer(&bd, &srd, &vertexBuffer));

	/// Vertex Input Layout
	// Input Element One: Position
	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	DEBUG_HR(d3dDevice->CreateInputLayout(
			ied,
			ARRAYSIZE(ied),
			vertShader.compile_result.compiledShaderBlob->GetBufferPointer(),
			vertShader.compile_result.compiledShaderBlob->GetBufferSize(),
			&inputLayout
	));
	d3dContext->IASetInputLayout(inputLayout.Get());
}
