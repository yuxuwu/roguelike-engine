#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

class Shader {
public:
	struct ShaderCompileResult {
		enum class Status {FAILURE, SUCCESS};
		Status status;
		std::string message;
	};
	enum class Type {Vertex, Fragment};

	Shader(const std::wstring&, const std::string&, Type);
	ShaderCompileResult getCompileResult() { return this->compile_result; }
private:
	ShaderCompileResult Compile(const std::wstring&, const std::string&, Type);
	ShaderCompileResult compile_result;

};

#endif