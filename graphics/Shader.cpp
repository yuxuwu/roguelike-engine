#include "Shader.h"
#include <sstream>
#include "../error_handling/WindowsErrorHandling.h"

static std::string ParseStringFromErrorBlob(ID3DBlob *errorBlob);
static std::string GetCompilationTarget(Shader::Type type);
static Shader::ShaderCompileResult CreateShaderCompileResult(ID3DBlob* compileErrors);
static std::string CreateShaderCompileMessage(ID3DBlob* compileErrors);


/*
 * =====================================================
 * Shader
 * =====================================================
 */
Shader::Shader(const std::wstring &filepath, const std::string &entrypoint, Shader::Type shaderType) {
	ShaderCompileResult tempCompResult = this->Compile(filepath, entrypoint, shaderType);
	this->compile_result = tempCompResult;
}


// TODO: Don't feel like passing in a shader blob object, should create one and return it
Shader::ShaderCompileResult Shader::Compile(const std::wstring& filepath, const std::string& entrypoint, Shader::Type shaderType) {
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

	return CreateShaderCompileResult(compileErrors);
}


static std::string ParseStringFromErrorBlob(ID3DBlob *errorBlob) {
	std::string result = (char*)errorBlob->GetBufferPointer();
	return result;
}

static std::string GetCompilationTarget(Shader::Type type) {
	switch(type) {
		case Shader::Type::Vertex: {
			return "vs_4_0";
		}
		case Shader::Type::Fragment: {
			return "ps_4_0";
		}
		default: {
			return "";
		}
	}
}

static Shader::ShaderCompileResult CreateShaderCompileResult(ID3DBlob* compileErrors) {
	std::string compileErrorMessage = CreateShaderCompileMessage(compileErrors);

	if (empty(compileErrorMessage)) {
		return {Shader::ShaderCompileResult::Status::SUCCESS, ""};
	}
	return {Shader::ShaderCompileResult::Status::FAILURE, compileErrorMessage};
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