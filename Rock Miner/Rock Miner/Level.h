#pragma once
#include <string>
#include <vector>

#include <GameEngine/SpriteBatch.h>
#include <GameEngine/TileSheet.h>
#include <glm/glm.hpp>

const float TILE_WIDTH = 64.0f;

class Level
{
public:
	Level(const std::string& fileName, SPH::TileSheet tileSheet);
	~Level();

	void renderLevel();

	glm::vec2 getPlayerStartPos() const { return m_playerStartPos; }
	const std::vector<glm::vec2>& getZombieStartPos() const { return m_zombieStartPos; }
	const std::vector<glm::vec2>& getRockStartPos() const { return m_rockStartPos; }
	const std::vector<glm::vec2>& getTreeStartPos() const { return m_treeStartPos; }

	int getWidth() const { return m_levelData[1].size(); }
	int getHeight() const { return m_levelData.size(); }
	int getNumHumans() const { return m_numHumans; }
	const std::vector<std::string>& getLevelData() const { return m_levelData; }
private:
	std::vector<std::string> m_levelData; //Holds tile data
	int m_numHumans = 0;
	SPH::SpriteBatch m_spriteBatch;

	glm::vec2 m_playerStartPos;
	std::vector<glm::vec2> m_zombieStartPos;
	std::vector<glm::vec2> m_rockStartPos;
	std::vector<glm::vec2> m_treeStartPos;
};

