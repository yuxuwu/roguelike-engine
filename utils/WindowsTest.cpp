#include <iostream>
#include "WindowsTest.h"

void WindowsTest::debug(UINT hr) {
	LPTSTR errorText = NULL;

	if(FAILED(hr)) {
		std::cout << "Call failed" << std::endl;
		FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM
				|FORMAT_MESSAGE_ALLOCATE_BUFFER
				|FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				hr,
				0,
				(LPTSTR)&errorText,
				0,
				NULL
		);
		if(NULL != errorText){
			std::wcout << "Error text: " << errorText << std::endl;
			LocalFree(errorText);
			errorText = NULL;
		}
	}
}