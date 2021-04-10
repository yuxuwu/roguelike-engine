#include "Shader.h"


static std::string CreateShaderCompileMessage(ID3DBlob*);
static std::string ParseStringFromErrorBlob(ID3DBlob*);


VertexShader::VertexShader(const ComPtr<ID3D11Device>& d3dDevice, const std::wstring& filepath, const std::string& entrypoint, D3D11_INPUT_ELEMENT_DESC ied[], UINT numIed) {
	ID3DBlob *compileErrors = nullptr;
	/// Compile Shader
	DEBUG_HR(
			D3DCompileFromFile(
					filepath.c_str(),                                 // filename
					nullptr,                                          // define shader macros (optional)
					nullptr,                                          // shader include files (optional)
					entrypoint.c_str(),                               // shader entry point function
					"vs_4_0", // compilation target
					0,                                                // compile options bitfield (optional)
					0,                                                // compile options 2 bitfield (optional)
					&this->compile_result.compiled_shaderblob,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);

	this->compile_result.message = CreateShaderCompileMessage(compileErrors);

	/// Create Shader
	DEBUG_HR(d3dDevice->CreateVertexShader(
			this->compile_result.compiled_shaderblob->GetBufferPointer(),
			this->compile_result.compiled_shaderblob->GetBufferSize(),
			nullptr,
			this->p_shader.GetAddressOf()
	));

	if(!this->compile_result.message.empty())
		std::cout << "SHADER COMPILE ERROR: " << this->compile_result.message << std::endl;


	/// Vertex Input Layout
	DEBUG_HR(d3dDevice->CreateInputLayout(
			ied,
			numIed,
			this->compile_result.compiled_shaderblob->GetBufferPointer(),
			this->compile_result.compiled_shaderblob->GetBufferSize(),
			&this->p_input_layout
	));
}

void VertexShader::Set(const ComPtr<ID3D11DeviceContext>& d3dContext) const {
	d3dContext->IASetInputLayout(this->p_input_layout.Get());
	d3dContext->VSSetShader(this->p_shader.Get(), nullptr, 0);
}



PixelShader::PixelShader(const ComPtr<ID3D11Device>& d3dDevice, const std::wstring& filepath, const std::string& entrypoint) {

	ID3DBlob *compileErrors = nullptr;
	DEBUG_HR(
			D3DCompileFromFile(
					filepath.c_str(),                                 // filename
					nullptr,                                          // define shader macros (optional)
					nullptr,                                          // shader include files (optional)
					entrypoint.c_str(),                               // shader entry point function
					"ps_4_0", // compilation target
					0,                                                // compile options bitfield (optional)
					0,                                                // compile options 2 bitfield (optional)
					&this->compile_result.compiled_shaderblob,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);

	this->compile_result.message = CreateShaderCompileMessage(compileErrors);

	DEBUG_HR(d3dDevice->CreatePixelShader(
			this->compile_result.compiled_shaderblob->GetBufferPointer(),
			this->compile_result.compiled_shaderblob->GetBufferSize(),
			nullptr,
			this->p_shader.GetAddressOf()
	));

	if(!this->compile_result.message.empty())
		std::cout << "SHADER COMPILE ERROR: " << this->compile_result.message << std::endl;
}

void PixelShader::Set(const ComPtr<ID3D11DeviceContext>& d3dContext) const {
	d3dContext->PSSetShader(this->p_shader.Get(), nullptr, 0);
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

static std::string ParseStringFromErrorBlob(ID3DBlob *errorBlob) {
	return (char*)errorBlob->GetBufferPointer();
}