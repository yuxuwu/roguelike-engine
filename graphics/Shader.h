#ifndef SHADER_H
#define SHADER_H


#include "../pch.h"

enum class ShaderType;

namespace Shader {
	struct ShaderCompileResult {
		enum class Status {FAILURE, SUCCESS};
		ID3D10Blob* compiledShaderBlob;
		Status status;
		std::string message;
	};

	struct CreateVertexShaderResult {
		ShaderCompileResult compile_result;
		ComPtr<ID3D11VertexShader> shader_object;
	};
	CreateVertexShaderResult CreateVertexShader(const std::wstring&, const std::string&, ComPtr<ID3D11Device>);



	class Shader {
	public:

		enum class ShaderType {Vertex, Pixel};

		Shader(const std::wstring&, const std::string&, ShaderType, ComPtr<ID3D11Device>);
		ShaderCompileResult getCompileResult() { return this->compile_result; }
		void* getShaderObject() { return this->shader_object;}

	private:
		ShaderCompileResult Compile(const std::wstring&, const std::string&, ShaderType);
		void CreateShaderObject(ComPtr<ID3D11Device> &d3dDevice);

		ShaderType type;
		void* shader_object = nullptr; // ComPtr<ID3D11VertexShader> or ComPtr<ID3D11PixelShader>
		ShaderCompileResult compile_result;
	};

}
#endif