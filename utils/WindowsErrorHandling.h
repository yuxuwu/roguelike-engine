#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <d3dcompiler.h>
#include <string>
#pragma comment(lib, "d3dcompiler.lib")

namespace WindowsErrorHandling {
	struct ComStatus {
		enum class Status {FAILURE, SUCCESS};

		Status status;
		std::wstring message;
	};

	ComStatus GetHRStatus(HRESULT hr);
}