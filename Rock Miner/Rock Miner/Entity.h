#pragma once
#include <glm/glm.hpp>
#include <GameEngine/GLTexture.h>
#include <GameEngine/SpriteBatch.h>
#include <GameEngine/ResourceManager.h>
#include "Level.h"

class Player;
class Agent;

const float ENTITY_WIDTH = TILE_WIDTH;
const float ENTITY_RADIUS = ENTITY_WIDTH / 2.0f;

class Entity
{
public:
	Entity();
	virtual ~Entity(); //virtual will call from inherited classes 

	virtual void update(float delta, const std::vector<std::string>& levelData, Player* player) = 0;

	void render(SPH::SpriteBatch& spriteBatch);

	bool collideWithAgent(Agent* agent);

	bool takeDamage(int damage);
	bool needsUpdate() const { return m_needsUpdate; }
	void needsUpdate(bool x) { m_needsUpdate = x; }

	glm::vec2 getPosition() const { return m_position; }
	void setPosition(glm::vec2 position) { m_position = position; }
	SPH::GLTexture getTexture() const { return m_texture; }

protected:	
	glm::vec2 m_position;
	glm::vec2 m_direction;
	float m_speed;
	int m_hp;
	int m_maxHP;

	bool m_needsUpdate = false;
	bool m_startTimer = true;
	int m_endTime = 0;
	int m_time = 0;

	SPH::GLTexture m_texture;
};