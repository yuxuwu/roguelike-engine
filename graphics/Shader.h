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

	static ShaderCompileResult Compile(ID3DBlob*, std::wstring, std::string, Type);

};

#endif