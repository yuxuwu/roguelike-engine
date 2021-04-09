//
// Created by Yu on 1/18/2021.
//

#ifndef ROGUELIKE_ENGINE_GAMEGRAPHICS_H
#define ROGUELIKE_ENGINE_GAMEGRAPHICS_H


#include "../pch.h"

struct Vertex {
	FLOAT X, Y, Z;
	FLOAT Color[3];
};

struct ShaderCompileResult {
	ID3D10Blob* compiledShaderBlob;
	std::string message;
};

struct VertexShaderCreateResult {
	ShaderCompileResult compile_result;
	ComPtr<ID3D11VertexShader> shader_object;
};

struct PixelShaderCreateResult {
	ShaderCompileResult compile_result;
	ComPtr<ID3D11PixelShader> shader_object;
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
	void Init(const HWND& hwnd);
	void renderFrame();
	void loadAndCompileTestShader();

	VertexShaderCreateResult CreateVertexShader(const std::wstring&, const std::string&);
	PixelShaderCreateResult CreatePixelShader(const std::wstring&, const std::string&);

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
