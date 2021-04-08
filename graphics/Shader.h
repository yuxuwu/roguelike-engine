#ifndef SHADER_H
#define SHADER_H


#include "../pch.h"

class Shader {
public:
	struct ShaderCompileResult {
		enum class Status {FAILURE, SUCCESS};
		ID3D10Blob* compiledShaderBlob;
		Status status;
		std::string message;
	};
	enum class Type {Vertex, Pixel};

	Shader(const std::wstring&, const std::string&, Type);
	ShaderCompileResult getCompileResult() { return this->compile_result; }
private:
	ShaderCompileResult Compile(const std::wstring&, const std::string&, Type);
	ShaderCompileResult compile_result;

};

#endif