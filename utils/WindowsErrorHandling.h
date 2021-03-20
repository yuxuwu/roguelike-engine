#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <d3dcompiler.h>
#include <string>
#pragma comment(lib, "d3dcompiler.lib")

namespace WindowsErrorHandling {
	struct ComResult {
		enum class Status {FAILURE, SUCCESS};

		Status status;
		std::wstring message;
	};

	ComResult DEBUGCheckWindowsCallOK(HRESULT hr);
	ComResult DEBUGCheckShaderOK(HRESULT file, ID3D10Blob* errorBlob);
}