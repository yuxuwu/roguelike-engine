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

	d3dSwapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(currentBackBuffer.ReleaseAndGetAddressOf()));

	d3dDevice->CreateRenderTargetView(
			currentBackBuffer.Get(),
			nullptr,
			backBuffer.ReleaseAndGetAddressOf());

	d3dContext->OMSetRenderTargets(
			1,
			backBuffer.GetAddressOf(),
			nullptr);
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
 * RENDERING START
 *************************************************************************/
void GameGraphics::renderFrame() {
	d3dContext->OMSetRenderTargets(1, backBuffer.GetAddressOf(), nullptr);
	clearRenderingTarget();

	for(auto rt : this->renderingTargets) {
		rt.Set(this->d3dContext);
		this->Render(rt);
	}

	d3dSwapChain->Present(1, 0);
}

void GameGraphics::clearRenderingTarget() {
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	d3dContext->ClearRenderTargetView(backBuffer.Get(), color);
}

void GameGraphics::Render(RenderingTarget renderingTarget) {
	renderingTarget.Set(this->d3dContext);
	d3dContext->Draw(3, 0);
}
/*************************************************************************
 * RENDERING END
 *************************************************************************/



void GameGraphics::loadAndCompileTestShader() {

	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	// Load Shaders
	VertexShader vertShader(this->d3dDevice, L"testfiles/shaders.shader", "VShader", ied, 1);
	PixelShader pixShader(this->d3dDevice, L"testfiles/shaders.shader", "PShader");

	// Load Vertex Data
	VERTEX OurVertices[] = {
			{0.0f, 0.5f, 0.0f},
			{0.45f, -0.5f, 0.0f},
			{-0.45f, -0.5f, 0.0f}
	};
	// Create Vertex Buffer
	VertexBuffer vertBuffer(this->d3dDevice, OurVertices, 3);

	RenderingTarget rt{vertShader, pixShader, vertBuffer};
	this->renderingTargets.emplace_back(rt);
}
