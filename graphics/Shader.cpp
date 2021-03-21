#include "Shader.h"
#include <sstream>
#include "../utils/WindowsErrorHandling.h"

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
	if(compileErrors){
		std::string compileErrorMessage("");
		compileErrorMessage = "A compile error was found for the shader: " +
							  ParseStringFromErrorBlob(compileErrors);
		compileErrors->Release();
		return {Shader::ShaderCompileResult::Status::FAILURE, compileErrorMessage};
	} else {
		return {Shader::ShaderCompileResult::Status::SUCCESS, ""};
	}
}

// TODO: Don't feel like passing in a shader blob object, should create one and return it
Shader::ShaderCompileResult Shader::Compile(ID3DBlob* shader, std::wstring filepath, std::string entrypoint, Shader::Type shaderType) {
	ID3DBlob *compileErrors = nullptr;
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