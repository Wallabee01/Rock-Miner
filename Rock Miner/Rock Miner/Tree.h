#pragma once
#include "Entity.h"
#include "Level.h"

const float TREE_WIDTH = 256.0f;
const float TREE_HEIGHT = 256.0f;
const float TREE_COLLISON_RADIUS = TILE_WIDTH / 3.5f;
const glm::vec2 TREE_COLLISION_OFFSET = glm::vec2(1.75f * TILE_WIDTH, 0.6f * TILE_WIDTH);

class Tree : public Entity
{
public:
	Tree(glm::vec2 pos, int hp, SPH::GLTexture texture);
	~Tree();

	virtual void update(float delta, const std::vector<std::string>& levelData, Player* player) override;
	void render(SPH::SpriteBatch& spriteBatch);

	bool collideWithAgent(Agent* agent);
};

