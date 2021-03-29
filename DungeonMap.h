#ifndef ROGUELIKE_ENGINE_DUNGEONMAP_H
#define ROGUELIKE_ENGINE_DUNGEONMAP_H

#include <string>
#include <vector>

class DungeonMap {
public:
	DungeonMap(std::vector<std::vector<char>> dungeonMap);
private:
	std::vector<std::vector<char>> dungeonMap;
};

DungeonMap GenerateDungeonMapFromString(const std::string& levelfile_as_string);

#endif //ROGUELIKE_ENGINE_DUNGEONMAP_H
