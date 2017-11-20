#include "Level.h"

#include <fstream>
#include <iostream>

#include <GameEngine/SpriteBatch.h>
#include <GameEngine/ResourceManager.h>

Level::Level(const std::string& fileName, SPH::TileSheet tileSheet) {
	std::ifstream file;

	file.open(fileName);
	if (file.fail()) {
		printf("Failed to load file. fileName = %s", fileName);
		system("pause");
		exit(1);
	}

	std::string line;

	while (getline(file, line)) {
		m_levelData.push_back(line);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	int row, col;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	SPH::Color whiteColor(255, 255, 255, 255);

	for (row = 0; row < m_levelData.size(); row++) {
		for (col = 0; col < m_levelData[row].size(); col++) {

			glm::vec4 destRect(col * TILE_WIDTH, row * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (m_levelData[row][col]) {
			case 'O': //Orange Brick
				m_spriteBatch.render(destRect, tileSheet.getUVs(0),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case '@': //Player
				m_spriteBatch.render(destRect, tileSheet.getUVs(10),
					tileSheet.texture.id, 0.0f, whiteColor);
				m_playerStartPos = glm::vec2(col * TILE_WIDTH, row * TILE_WIDTH);
				m_levelData[row][col] = '.';
				break;
			case 'Z'://Zombie
				m_spriteBatch.render(destRect, tileSheet.getUVs(10),
					tileSheet.texture.id, 0.0f, whiteColor);
				m_zombieStartPos.emplace_back(col * TILE_WIDTH, row * TILE_WIDTH);
				m_levelData[row][col] = '.';
				break;
			case '^': //Rock
				m_spriteBatch.render(destRect, tileSheet.getUVs(10),
					tileSheet.texture.id, 0.0f, whiteColor);
				m_rockStartPos.emplace_back(col * TILE_WIDTH, row * TILE_WIDTH);
				m_levelData[row][col] = '.';
				break;
			case '.'://Ground
				m_spriteBatch.render(destRect, tileSheet.getUVs(10),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 't': //Grassy Stone Wall
				m_spriteBatch.render(destRect, tileSheet.getUVs(10),
					tileSheet.texture.id, 0.0f, whiteColor);
				m_treeStartPos.emplace_back(col * TILE_WIDTH, row * TILE_WIDTH);
				m_levelData[row][col] = '.';
				break;
			case ','://Ground 2
				m_spriteBatch.render(destRect, tileSheet.getUVs(12),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case '"'://Ground 3
				m_spriteBatch.render(destRect, tileSheet.getUVs(14),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case ':'://Ground 4
				m_spriteBatch.render(destRect, tileSheet.getUVs(16),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'G': //Brick
				m_spriteBatch.render(destRect, tileSheet.getUVs(4),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'g': //Glass
				m_spriteBatch.render(destRect, uvRect,
					SPH::ResourceManager::getTexture("Textures/glass2.png").id, 0.0f, whiteColor);
				break;
			case 'b': //Grass 1
				m_spriteBatch.render(destRect, tileSheet.getUVs(20),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'B': //Grass 2
				m_spriteBatch.render(destRect, tileSheet.getUVs(22),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'v': //Grass 3
				m_spriteBatch.render(destRect, tileSheet.getUVs(24),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'V': //Grass 4
				m_spriteBatch.render(destRect, tileSheet.getUVs(26),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case ';': //Stone ground
				m_spriteBatch.render(destRect, tileSheet.getUVs(41),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'l': //Stone ground
				m_spriteBatch.render(destRect, tileSheet.getUVs(43),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case 'k': //Stone ground
				m_spriteBatch.render(destRect, tileSheet.getUVs(45),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case '>': //Stone descending stairs
				m_spriteBatch.render(destRect, tileSheet.getUVs(49),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case '<': //Stone ascending stairs
				m_spriteBatch.render(destRect, tileSheet.getUVs(48),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			case '#': //Grassy Stone Wall
				m_spriteBatch.render(destRect, tileSheet.getUVs(46),
					tileSheet.texture.id, 0.0f, whiteColor);
				break;
			default:
				printf("Unrecognized Tile: %c Location: %i, %i\n", m_levelData[row][col], row, col);
				break;
			}
		}
	}

	m_spriteBatch.end();

}


Level::~Level()
{
}

void Level::renderLevel() {
	m_spriteBatch.renderBatch();
}