#include "Tree.h"
#include "Agent.h"


Tree::Tree(glm::vec2 pos, int hp, SPH::GLTexture texture)
{
	m_position = pos;
	m_hp = hp;
	m_maxHP = hp;
	m_texture = texture;
}


Tree::~Tree()
{
}

void Tree::update(float delta, const std::vector<std::string>& levelData, Player* player)
{

}

void Tree::render(SPH::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x, m_position.y, TREE_WIDTH, TREE_HEIGHT);

	spriteBatch.render(destRect, uvRect, m_texture.id, 0.0f, SPH::Color(255, 255, 255, 255));
}

bool Tree::collideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = TREE_COLLISON_RADIUS + AGENT_RADIUS;

	glm::vec2 centerPosA = m_position + glm::vec2(2.0f * TILE_WIDTH, 0.5f * TILE_WIDTH) + glm::vec2(TREE_COLLISON_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
		//agent->m_position -= collisionDepthVec;
		return true;
	}

	return false;
}
