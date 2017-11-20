#include "Agent.h"
#include <GameEngine/ResourceManager.h>
#include "Level.h"

#include <algorithm>

Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::render(SPH::SpriteBatch& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x, m_position.y, AGENT_WIDTH, AGENT_WIDTH);

	spriteBatch.render(destRect, uvRect, m_textureID, 0.0f, m_color, m_direction);
}

bool Agent::collideWithLevel(const std::vector<std::string>& lvlData) {

	std::vector<glm::vec2> collideTilePos;

	//Check bottom left corner
	checkTilePos(collideTilePos, lvlData, m_position.x, m_position.y);
	//bottom right corner
	checkTilePos(collideTilePos, lvlData, m_position.x + AGENT_WIDTH, m_position.y);
	//top left corner
	checkTilePos(collideTilePos, lvlData, m_position.x, m_position.y + AGENT_WIDTH);
	//top right corner
	checkTilePos(collideTilePos, lvlData, m_position.x + AGENT_WIDTH, m_position.y + AGENT_WIDTH);

	if (collideTilePos.size() == 0) { return false; }

	for (int i = 0; i < collideTilePos.size(); i++) {
		collideWithTile(collideTilePos[i]);
	}
	return true;
}

void Agent::checkTilePos(std::vector<glm::vec2>& collideTilePos, const std::vector<std::string>& lvlData, float x, float y) {
	
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH), floor(y / (float)TILE_WIDTH));

	//If agent is outside level
	if (cornerPos.x < 0 || cornerPos.x >= lvlData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= lvlData.size()) return;

	// ADD MORE WALKABLE TILES HERE
	if (lvlData[cornerPos.y][cornerPos.x] != '.' && lvlData[cornerPos.y][cornerPos.x] != ';' &&
		lvlData[cornerPos.y][cornerPos.x] != 'b' && lvlData[cornerPos.y][cornerPos.x] != 'B' &&
		lvlData[cornerPos.y][cornerPos.x] != 'v' && lvlData[cornerPos.y][cornerPos.x] != 'V' &&
		lvlData[cornerPos.y][cornerPos.x] != 'l' && lvlData[cornerPos.y][cornerPos.x] != 'k' &&
		lvlData[cornerPos.y][cornerPos.x] != '"' && lvlData[cornerPos.y][cornerPos.x] != ',' &&
		lvlData[cornerPos.y][cornerPos.x] != ':' && lvlData[cornerPos.y][cornerPos.x] != '>' &&
		lvlData[cornerPos.y][cornerPos.x] != '<')
	{ 
		collideTilePos.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Agent::collideWithTile(glm::vec2 tilePos) {

	const float TILE_RADIUS = TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerAgentPos = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerAgentPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	if (xDepth > 0 && yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distVec.x < 0) {
				m_position.x -= xDepth;
			}
			else {
				m_position.x += xDepth;
			}
		}
		else {
			if (distVec.y < 0) {
				m_position.y -= yDepth;
			}
			else {
				m_position.y += yDepth;
			}
		}
	}
}

bool Agent::collideWithAgent(Agent* agent) {
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

	glm::vec2 centerPosA = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;
	glm::vec2 direction = glm::normalize(distVec);

	float dist = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - dist;
	if (collisionDepth > 0) {
		m_position += (direction * collisionDepth) / 2.0f;
		agent->m_position -= (direction * collisionDepth) / 2.0f;
		return true;
	}
	return false;

}

bool Agent::takeDmg(int dmg) {
	m_health -= dmg;

	if (m_health <= 0) {
		return true;
	}
	return false;
}

bool Agent::collideWithEntity(Entity* entity)
{
	const float MIN_DISTANCE = AGENT_RADIUS + ENTITY_RADIUS / 2;

	glm::vec2 centerPosA = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(ENTITY_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
		m_position += collisionDepthVec / 2.0f;
		//entity->setPosition(entity->getPosition() -= collisionDepthVec / 2.0f);
		return true;
	}

	return false;
}