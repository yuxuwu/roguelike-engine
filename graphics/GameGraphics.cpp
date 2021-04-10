//
// Created by Yu on 1/18/2021.
//
#ifndef UNICODE
#define UNICODE
#endif

#include "GameGraphics.h"

void GameGraphics::Init(const HWND& hwnd) {
	setupD3DDeviceAndSwapChain(hwnd);
	setupRenderTargets();
	setupViewport(hwnd);
}



/*************************************************************************
 * D3D SETUP START
 *************************************************************************/
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
/*************************************************************************
 * D3D SETUP END
 *************************************************************************/



/*************************************************************************
 * SHADERS START
 *************************************************************************/




/*************************************************************************
 * SHADERS END
 *************************************************************************/



/*************************************************************************
 * VERTEX START
 *************************************************************************/
struct VERTEX {
	float X, Y, Z; // Vertex Position
};
/*************************************************************************
 * VERTEX END
 *************************************************************************/



/*************************************************************************
 * RENDERING START
 *************************************************************************/
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
/*************************************************************************
 * RENDERING START
 *************************************************************************/



void GameGraphics::loadAndCompileTestShader() {

	// Load Shaders
	VertexShader vertShader = VertexShader(this->d3dDevice, L"testfiles/shaders.shader", "VShader");
	PixelShader pixShader = PixelShader(this->d3dDevice, L"testfiles/shaders.shader", "PShader");
	vertShader.Set(this->d3dContext);
	pixShader.Set(this->d3dContext);

	// Load Vertex Data
	VERTEX OurVertices[] = {
			{0.0f, 0.5f, 0.0f},
			{0.45f, -0.5f, 0.0f},
			{-0.45f, -0.5f, 0.0f}
	};

	// Create Vertex Buffer
	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA srd = {OurVertices, 0, 0};
	DEBUG_HR(d3dDevice->CreateBuffer(&bd, &srd, &vertexBuffer));

	/// Vertex Input Layout
	// Create Vertex Input Layout
	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	DEBUG_HR(d3dDevice->CreateInputLayout(
			ied,
			ARRAYSIZE(ied),
			vertShader.compile_result.compiled_shaderblob->GetBufferPointer(),
			vertShader.compile_result.compiled_shaderblob->GetBufferSize(),
			&inputLayout
	));

	// Set Input Layout
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	d3dContext->IASetInputLayout(inputLayout.Get());
	d3dContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}