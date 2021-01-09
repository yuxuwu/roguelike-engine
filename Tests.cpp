#include <gtest/gtest.h>
#include "WinMain.cpp"

#include <string>
#include <vector>

using namespace std;

TEST (Meta, IsGTestWorking) {
	EXPECT_EQ(1, 1);
}

TEST (FileImports, ReadFileToStringWorks) {
	string filename = "./testfiles/test";

	EXPECT_EQ(importFileToString(filename), "Hello, World!\nThis is a test file.");
}

TEST (FileImports, ReadSymbolsToStringWorks) {
	string filename = "./testfiles/one.level";

	EXPECT_EQ(importFileToString(filename), "###\n###\n###");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}