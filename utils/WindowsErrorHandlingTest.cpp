#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "WindowsErrorHandling.h"

using ::testing::HasSubstr;

TEST (WindowsErrorHandling, WindowsCOMCallsShouldReturnFailureMessage) {
	HRESULT hr_failure = 0x80010114; // Code for RPC_E_INVALID_OBJECT

	WindowsErrorHandling::ComResult result = WindowsErrorHandling::DEBUGCheckWindowsCallOK(hr_failure);
	EXPECT_EQ(result.status, WindowsErrorHandling::ComResult::Status::FAILURE);
	EXPECT_THAT(result.message, HasSubstr(L"The requested object does not exist"));
}

TEST (WindowsErrorHandling, WindowsCOMCallsShouldReturnEmptySuccessMessage) {
	HRESULT hr_success = 0x00000000; // 0 means success in HRESULT

	WindowsErrorHandling::ComResult result = WindowsErrorHandling::DEBUGCheckWindowsCallOK(hr_success);
	EXPECT_EQ(result.status, WindowsErrorHandling::ComResult::Status::SUCCESS);
	EXPECT_THAT(result.message, L"");
}

//TEST (WindowsErrorHandling, ShaderCompileShouldGiveFailureMessage)