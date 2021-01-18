#include <iostream>
#include "WindowsTest.h"

void WindowsTest::debug(UINT hr) {
	if(FAILED(hr)) {
		std::cout << "Call failed" << std::endl;
	}
}