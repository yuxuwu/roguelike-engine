#include "Shader.h"
#include <sstream>
#include "../error_handling/WindowsErrorHandling.h"



Shader::CreateVertexShaderResult Shader::CreateVertexShader(const std::wstring& filepath, const std::string& entrypoint, ComPtr<ID3D11Device> d3dDevice) {
	CreateVertexShaderResult shaderResult{{nullptr, ShaderCompileResult::Status::SUCCESS, ""}};

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
					&shaderResult.compile_result.compiledShaderBlob,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);


	DEBUG_HR(d3dDevice->CreateVertexShader(
					shaderResult.compile_result.compiledShaderBlob->GetBufferPointer(),
					shaderResult.compile_result.compiledShaderBlob->GetBufferSize(),
					nullptr,
					shaderResult.shader_object.GetAddressOf()
			 ));

	return shaderResult;
}

/*
static std::string ParseStringFromErrorBlob(ID3DBlob *);
static std::string GetCompilationTarget(Shader::ShaderType);
static Shader::ShaderCompileResult CreateShaderCompileResult(ID3DBlob*, ID3DBlob*);
static std::string CreateShaderCompileMessage(ID3DBlob*);

Shader::Shader(const std::wstring &filepath, const std::string &entrypoint, Shader::ShaderType shaderType, ComPtr<ID3D11Device> d3dDevice) {
	this->type = shaderType;

	ShaderCompileResult tempCompResult = this->Compile(filepath, entrypoint, shaderType);
	this->compile_result = tempCompResult;

	this->CreateShaderObject(d3dDevice);
}

void Shader::CreateShaderObject(ComPtr<ID3D11Device> &d3dDevice) {

}


// TODO: Don't feel like passing in a shader blob object, should create one and return it
Shader::ShaderCompileResult Shader::Compile(const std::wstring& filepath, const std::string& entrypoint, Shader::ShaderType shaderType) {
	ID3DBlob *compileErrors = nullptr;
	ID3DBlob *shader = nullptr;
	DEBUG_HR(
		D3DCompileFromFile(
				filepath.c_str(),                         // filename
				nullptr,                                  // define shader macros (optional)
				nullptr,                                  // shader include files (optional)
				entrypoint.c_str(),                       // shader entry point function
				GetCompilationTarget(shaderType).c_str(), // compilation target
				0,                                        // compile options bitfield (optional)
				0,                                        // compile options 2 bitfield (optional)
				&shader,                                  // p to compiled code
				&compileErrors)                           // p to error msgs, NULL if no errors (optional)
	);

	return CreateShaderCompileResult(shader, compileErrors);
}


static std::string ParseStringFromErrorBlob(ID3DBlob *errorBlob) {
	std::string result = (char*)errorBlob->GetBufferPointer();
	return result;
}

static std::string GetCompilationTarget(Shader::Type type) {
	switch(type) {
		case Shader::ShaderType::Vertex: {
			return "vs_4_0";
		}
		case Shader::ShaderType::Pixel: {
			return "ps_4_0";
		}
		default: {
			return "";
		}
	}
}

static Shader::ShaderCompileResult CreateShaderCompileResult(ID3DBlob* compiledShaderBlob, ID3DBlob* compileErrors) {
	std::string compileErrorMessage = CreateShaderCompileMessage(compileErrors);

	if (empty(compileErrorMessage)) {
		return {compiledShaderBlob, Shader::ShaderCompileResult::Status::SUCCESS, ""};
	}
	return {nullptr, Shader::ShaderCompileResult::Status::FAILURE, compileErrorMessage};
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

 */