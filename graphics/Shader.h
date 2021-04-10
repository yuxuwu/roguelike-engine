#ifndef ROGUELIKE_ENGINE_SHADER_H
#define ROGUELIKE_ENGINE_SHADER_H

#include "../pch.h"

struct ShaderCompileResult {
	ID3D10Blob* compiled_shaderblob;
	std::string message;
};

struct VertexShader {
	VertexShader(const ComPtr<ID3D11Device>&, const std::wstring&, const std::string&);
	void Set(ComPtr<ID3D11DeviceContext>);

	ShaderCompileResult compile_result;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> p_shader;
};

struct PixelShader {
	PixelShader(const ComPtr<ID3D11Device>&, const std::wstring&, const std::string&);
	void Set(ComPtr<ID3D11DeviceContext>);

	ShaderCompileResult compile_result;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> p_shader;
};

#endif //ROGUELIKE_ENGINE_SHADER_H
