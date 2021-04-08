#include <gtest/gtest.h>
#include "../pch.h"

#include "../graphics/Shader.h"


//TODO: Need to mock out ComPtr<ID3D11Device>, perhaps make a virtual GameGraphics class
class ShaderSuccessTest : public ::testing::Test {
protected:
	void SetUp() override {
		shaderSuccess = Shader::CreateVertexShader(L"testfiles/shaders.shader", "VShader");
	}
	Shader::CreateVertexShaderResult shaderSuccess;

};

class ShaderFailureTest : public ::testing::Test {
protected:
	void SetUp() override {
		shaderFailure = Shader::CreateVertexShader(L"testfiles/syntax_error.shader", "VShader");
	}
	Shader::CreateVertexShaderResult shaderFailure;

};


TEST_F (ShaderSuccessTest, ReturnsSuccessOnValidShader) {
	EXPECT_EQ(shaderSuccess.compile_result.status, Shader::ShaderCompileResult::Status::SUCCESS);
}

TEST_F (ShaderSuccessTest, HasNonNullShaderBlobOnSuccess) {
	EXPECT_NE(shaderSuccess.compile_result.compiledShaderBlob->GetBufferPointer(), nullptr);
}

TEST_F (ShaderSuccessTest, CreateID3DShaderOnValidShader) {
	EXPECT_NE(shaderSuccess.shader_object, nullptr);
}

TEST_F (ShaderFailureTest, ReturnsFailureOnInvalidFilepath) {
	EXPECT_EQ(shaderFailure.compile_result.status, Shader::ShaderCompileResult::Status::FAILURE);
	EXPECT_NE(shaderFailure.compile_result.message, "");
}

TEST_F (ShaderFailureTest, HasNullShaderObjectOnFailure) {
	EXPECT_EQ(shaderFailure.shader_object, nullptr);
}