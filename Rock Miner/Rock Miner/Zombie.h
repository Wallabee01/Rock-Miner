#pragma once
#include "Agent.h"

class Human;

class Zombie: public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos, GLuint textureID);

	virtual void update(float deltaTime, const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;

private:
	Human* getNearestHuman(std::vector<Human*>& humans);
};

