#ifndef ROGUELIKE_ENGINE_GAMEGRAPHICS_H
#define ROGUELIKE_ENGINE_GAMEGRAPHICS_H


#include "../pch.h"
#include "Shader.h"
#include "Vertices.h"
#include "RenderingTarget.h"

class GameGraphics {
private:
	static constexpr D3D_FEATURE_LEVEL _levels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
	};


public:
	void Init(const HWND& hwnd);
	void renderFrame();
	void loadAndCompileTestShader();


private:
	void setupD3DDeviceAndSwapChain(const HWND &hwnd);
	void setupRenderTargets();
	void setupViewport(const HWND& hwnd);
	void clearRenderingTarget();
private:
	D3D_FEATURE_LEVEL d3dFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> d3dSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;

};


#endif //ROGUELIKE_ENGINE_GAMEGRAPHICS_H
