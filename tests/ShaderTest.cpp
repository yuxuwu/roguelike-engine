#include <gtest/gtest.h>
#include "../graphics/Shader.h"

/*
struct ShaderCompileStatus {
	enum class Status {FAILURE, SUCCESS};

	Status status;
	std::wstring errorMsg;
};

struct ShaderCompileResult {
	ShaderCompileStatus compileStatus;
	ShaderObject shader;
};

struct ShaderProgramResult {
	ShaderProgramObject shaderProgram;
};

// How should the Objects be passed in? Copied in/out or as references?

ShaderCompileResult compileVertexShader(linkToShaderFile);
ShaderCompileResult compileFragShader(linkToShaderFile);
ShaderCompileResult compileShader(linkToShaderFile);

ShaderProgramResult loadShaderProgram(vertexObject, fragObject);
ShaderProgramResult loadShaderProgram(linkToVertexShader, linkToFrameShader);
*/

/// Compiled Shader code to blob
// ID3DBlob errorBlob
// ID3DBlob shader

/// Device: Create Shader in GPU from blob
// ComPtr<ID3D11VertexShader>
// ComPtr<ID3D11PixelShader>

/// Context: Set shader


TEST (ShaderCompile, ReturnsSuccessOnValidFile) {
	Shader shader(L"testfiles/shaders.shader", "VShader", Shader::Type::Vertex);
	EXPECT_EQ(shader.getCompileResult().status, Shader::ShaderCompileResult::Status::SUCCESS);
	EXPECT_EQ(shader.getCompileResult().message, "");
}

TEST (ShaderCompile, ReturnsFailureOnInvalidFilepath) {
	Shader shader(L"testfiles/syntax_error.shader", "VShader", Shader::Type::Vertex);
	EXPECT_EQ(shader.getCompileResult().status, Shader::ShaderCompileResult::Status::FAILURE);
	EXPECT_NE(shader.getCompileResult().message, "");
}