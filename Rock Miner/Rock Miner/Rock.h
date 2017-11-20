#pragma once
#include "Entity.h"
#include <GameEngine/GLTexture.h>

const float ROCK_WIDTH = 64.0f;
const float ROCK_RADIUS = ROCK_WIDTH / 2.0f;

class Rock : public Entity
{
public:
	Rock(glm::vec2 pos, int hp, SPH::GLTexture texture);
	virtual ~Rock();

	virtual void update(float delta, const std::vector<std::string>& levelData, Player* player) override;
	void render(SPH::SpriteBatch& spriteBatch);
private:
};
