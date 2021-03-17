#include <iostream>
#include <sstream>
#include "WindowsErrorHandling.h"

/*
 * TODO: Should make these macros, since macros allow you
 *       to get the line # and file
 */

static std::wstring GetHResultDescription(UINT);
static std::wstring GetShaderCompilerErrorMessage(ID3D10Blob*);

void WindowsErrorHandling::DEBUGCheckOK(HRESULT hr) {
	if(FAILED(hr)) {
		std::cout << "Call Failed" << std::endl;
		std::wcout << GetHResultDescription(hr) << std::endl;
	}
}

void WindowsErrorHandling::DEBUGCheckShaderOK(HRESULT hr, ID3D10Blob* errorBlob) {
	DEBUGCheckOK(hr);
	std::wcout << GetShaderCompilerErrorMessage(errorBlob) << std::endl;
}

static std::wstring GetHResultDescription(UINT hr) {
	std::wstring result{};

	LPTSTR errorTextBuffer = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM
		|FORMAT_MESSAGE_ALLOCATE_BUFFER
		|FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, //Not used
		hr,
		0, //Language: Default
		(LPTSTR)&errorTextBuffer,
		0, //Memory size, not used since using allocate flag
		nullptr
	);
	if(nullptr != errorTextBuffer){
		std::wstringstream resultString{};
		resultString << "Error code: " << std::hex << "0x" << hr << std::endl;
		resultString << "Error text: " << errorTextBuffer << std::endl;

		result = resultString.str();
		LocalFree(errorTextBuffer);
		errorTextBuffer = nullptr;
	} else {
		std::cout << "errorTextBuffer was empty/null" << std::endl;
	}

	return result;
}

static std::wstring GetShaderCompilerErrorMessage(ID3D10Blob *errorBlob) {
	std::wstring result{};

	if(errorBlob){
		char* compileErrors = (char*)errorBlob->GetBufferPointer();

		std::wstringstream resultString{};
		resultString << "There was a shader compilation error" << std::endl;
		resultString << compileErrors << std::endl;

		result = resultString.str();
		errorBlob->Release();
	}

	return result;
}