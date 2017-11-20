#include "Rock.h"
#include <GameEngine/ResourceManager.h>
#include "Level.h"
#include <ctime>

#include <SDL.h>
#include <iostream>

const int DELAY_IN_SECONDS = 9;
const int TIME_TO_MINE_IN_SECONDS = 3;

Rock::Rock(glm::vec2 pos, int hp, SPH::GLTexture texture)
{
	m_position = pos; 
	m_hp = hp; 
	m_maxHP = hp;
	m_texture = texture;
}


Rock::~Rock()
{
}

void Rock::update(float delta, const std::vector<std::string>& levelData, Player* player)
{
	//needsUpdate set when rock is clicked
	//if (m_needsUpdate) {
	//	if (m_startTimer) {
	//		m_endTime = time(NULL) + DELAY_IN_SECONDS;
	//		m_startTimer = false;
	//	}
	//	m_time = time(NULL);

	//	//Delay changing texture until rock is mined
	//	//TIME_TO_MINE should be a variable of player
	//	if (m_texture.id == m_fullTexture.id) {
	//		if (m_time == m_endTime - TIME_TO_MINE_IN_SECONDS) {
	//			m_texture = m_emptyTexture;
	//		}
	//	}


	//	if (m_time == m_endTime) {
	//		m_texture = m_fullTexture;
	//		m_needsUpdate = false;
	//		m_startTimer = true;
	//	}
	//}
}

void Rock::render(SPH::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x, m_position.y, ROCK_WIDTH, ROCK_WIDTH);

	spriteBatch.render(destRect, uvRect, m_texture.id, 0.0f, SPH::Color(255, 255, 255, 255));
}
