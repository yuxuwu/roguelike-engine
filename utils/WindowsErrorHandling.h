#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <d3dcompiler.h>
#include <string>
#include <iostream>
#pragma comment(lib, "d3dcompiler.lib")

#ifndef NDEBUG
#define DEBUG_HR(hr) { \
	::WindowsErrorHandling::ComStatus status = ::WindowsErrorHandling::GetHRStatus(hr); \
	if(status.status == ::WindowsErrorHandling::ComStatus::Status::FAILURE){            \
    	std::wcout << L"On line " << __LINE__ << L"in file " << __FILE__ << std::endl;  \
		std::wcout << status.message << std::endl;                                      \
	}                                                                                   \
}
#else
#define DEBUG_HR(x)
#endif

// TODO: Might be better to implement as Macros to get file name and position
namespace WindowsErrorHandling {
	struct ComStatus {
		enum class Status {FAILURE, SUCCESS};

		Status status;
		std::wstring message;
	};

	ComStatus GetHRStatus(HRESULT hr);
}