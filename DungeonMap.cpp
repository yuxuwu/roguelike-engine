#include "DungeonMap.h"

DungeonMap::DungeonMap(std::vector<std::vector<char>> dungeonMap) {
	this->dungeonMap = dungeonMap;
}

DungeonMap GenerateDungeonMapFromString(const std::string& levelfile_as_string)
{
	std::vector<std::vector<char>> dungeonMap;
	dungeonMap.emplace_back();
	for(int i = 0; i < levelfile_as_string.size(); ++i) {
		if(levelfile_as_string[i] == '\n') {
			dungeonMap.emplace_back();
		} else {
			dungeonMap.back().emplace_back(levelfile_as_string[i]);
		}
	}
	return DungeonMap(dungeonMap);
}
