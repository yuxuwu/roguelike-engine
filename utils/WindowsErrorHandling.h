#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

namespace WindowsErrorHandling {
	void DEBUGCheckOK(HRESULT hr);
	void DEBUGCheckShaderOK(HRESULT file, ID3D10Blob* errorBlob);
}