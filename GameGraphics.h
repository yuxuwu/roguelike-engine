//
// Created by Yu on 1/18/2021.
//

#ifndef ROGUELIKE_ENGINE_GAMEGRAPHICS_H
#define ROGUELIKE_ENGINE_GAMEGRAPHICS_H


#include "pch.h"

struct Vertex {
	FLOAT X, Y, Z;
	FLOAT Color[3];
};

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
	void setupGraphics(const HWND& hwnd);
	void renderFrame();
	void loadAndCompileTestShader();
private:
	void _setupD3DDeviceAndSwapChain(const HWND &hwnd);
	void _setupRenderTargets();
	void _setupViewport(const HWND& hwnd);
	void _clearRenderingTarget();
private:
	D3D_FEATURE_LEVEL _d3dFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device> _d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> _d3dSwapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _backBuffer;

};


#endif //ROGUELIKE_ENGINE_GAMEGRAPHICS_H
