#pragma once
#include <glm/glm.hpp>

#include <GameEngine/GameEngine.h>
#include <GameEngine/SpriteBatch.h>

#include "Entity.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent(); // virtual destructor on the parent class will allow child class destructor to be called instead of parent class destructor

	virtual void update(float deltaTime, const std::vector<std::string>& levelData) = 0; // every child class has to implement virtual classes of parent

	bool collideWithLevel(const std::vector<std::string>& lvlData);

	bool collideWithAgent(Agent* agent);
	bool collideWithEntity(Entity* entity);

	void render(SPH::SpriteBatch& spriteBatch);

	void setPosition(glm::vec2 position) { m_position = position; }
	glm::vec2 getPosition() const { return m_position; }

	bool takeDmg(int dmg);

	int AgentID() const { return m_agentID; }
	void AgentID(int val) { m_agentID = val; }
protected:
	void checkTilePos(std::vector<glm::vec2>& collideTilePos, const std::vector<std::string>& lvlData, float x, float y);
	void collideWithTile(glm::vec2 tilePos);

	GLuint m_textureID;
	glm::vec2 m_position;
	glm::vec2 m_direction = glm::vec2(1.0f, 0.0f);
	SPH::Color m_color;
	float m_speed;
	int m_health;
	char collidedTile;
	int m_agentID;
};

