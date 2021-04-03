#include <gtest/gtest.h>
#include "../graphics/Shader.h"


class ShaderSuccessTest : public ::testing::Test {
protected:
	void SetUp() override {
		shaderSuccess = new Shader(L"testfiles/shaders.shader", "VShader", Shader::Type::Vertex);
	}
	Shader* shaderSuccess;
};

class ShaderFailureTest : public ::testing::Test {
protected:
	void SetUp() override {
		shaderFailed = new Shader(L"testfiles/syntax_error.shader", "VShader", Shader::Type::Vertex);
	}
	Shader* shaderFailed;
};

TEST_F (ShaderSuccessTest, ReturnsSuccessOnValidFile) {
	EXPECT_EQ(shaderSuccess->getCompileResult().status, Shader::ShaderCompileResult::Status::SUCCESS);
}

TEST_F (ShaderSuccessTest, HasNonNullShaderBlobOnSuccess) {
	EXPECT_NE(shaderSuccess->getCompileResult().compiledShaderBlob, nullptr);
}

TEST_F (ShaderFailureTest, ReturnsFailureOnInvalidFilepath) {
	EXPECT_EQ(shaderFailed->getCompileResult().status, Shader::ShaderCompileResult::Status::FAILURE);
	EXPECT_NE(shaderFailed->getCompileResult().message, "");
}

