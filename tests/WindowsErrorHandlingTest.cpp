#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../utils/WindowsErrorHandling.h"

using ::testing::HasSubstr;
using namespace WindowsErrorHandling;

TEST (WindowsErrorHandling, GetHRStatusReturnsFailureMsg) {
	HRESULT hr_failure = 0x80010114; // Code for RPC_E_INVALID_OBJECT

	ComStatus result = GetHRStatus(hr_failure);
	EXPECT_EQ(result.status, ComStatus::Status::FAILURE);
	EXPECT_THAT(result.message, HasSubstr(L"The requested object does not exist"));
}

TEST (WindowsErrorHandling, GetHRStatusReturnsSuccessMsg) {
	HRESULT hr_success = 0x00000000; // 0 means success in HRESULT

	ComStatus result = GetHRStatus(hr_success);
	EXPECT_EQ(result.status, ComStatus::Status::SUCCESS);
	EXPECT_THAT(result.message, L"");
}