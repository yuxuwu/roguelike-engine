#include <gtest/gtest.h>

#include "error_handling/FileHandling.h"
#include "DungeonMap.h"

#include <string>
#include <vector>

using namespace std;
using namespace Utils;

TEST (Init, IsGTestWorking) {
	EXPECT_EQ(1, 1);
}

TEST (FileImports, ReadFileToStringWorks) {
	string filename = "./testfiles/test";

	string output = importFileToString(filename);

	string result = "Hello, World!\nThis is a test file.";
	EXPECT_EQ(output, result);
}

TEST (FileImports, ReadSymbolsToStringWorks) {
	string filename = "./testfiles/one.level";

	string output = importFileToString(filename);

	string result = "###\n###\n###";
	EXPECT_EQ(output, result);
}

/*
TEST (FileImports_DungeonMap, CreateDungeonFromSymbolsWorks) {
	string dungeonmap_file = "./testfiles/one.level";

	auto output = GenerateDungeonMapFromString(importFileToString(dungeonmap_file)).dungeonMap;

	std::vector<std::vector<char>> result = {{'#', '#', '#'}, {'#', '#', '#'}, {'#', '#', '#'}};
	EXPECT_EQ(output, result);
}
*/