#include "Entity.h"
#include "Agent.h"
#include "Level.h"
#include <algorithm>

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::render(SPH::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x, m_position.y, ENTITY_WIDTH, ENTITY_WIDTH);

	spriteBatch.render(destRect, uvRect, m_texture.id, 0.0f, SPH::Color(255, 255, 255, 255));
}

bool Entity::collideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = ENTITY_RADIUS + AGENT_RADIUS;

	glm::vec2 centerPosA = m_position + glm::vec2(ENTITY_RADIUS);
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

bool Entity::takeDamage(int damage)
{
	m_hp -= damage;
	if (m_hp <= 0) return true;
	else return false;
}