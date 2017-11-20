#pragma once
#include <GameEngine/InputManager.h>
#include <GameEngine/Camera2D.h>
#include <GameEngine/TileSheet.h>
#include "Agent.h"
#include "Tree.h"

const float PLAYER_WIDTH = 84.0f;
const float PLAYER_RADIUS = PLAYER_WIDTH / 2.0f;
enum class Direction {UP, DOWN, LEFT, RIGHT};
enum class PlayerState { ATTACKING, IDLE, MOVING};

class Player: public Agent
{
public:
	Player();
	virtual ~Player();

	void init(glm::vec2 position, float speed, SPH::GLTexture texture, SPH::InputManager* inputManager,
		SPH::Camera2D* camera);

	virtual void update(float deltaTime, const std::vector<std::string>& levelData) override;

	void render(SPH::SpriteBatch& spriteBatch);

	bool collideWithTree(Tree* tree);

private:
	SPH::InputManager* m_inputManager;
	SPH::Camera2D* m_camera;
	SPH::TileSheet m_texture;
	Direction m_lastDirection = Direction::DOWN;
	Direction m_movementDirection = Direction::DOWN;
	PlayerState m_playerState = PlayerState::IDLE;
	bool m_isAttacking;
	float m_animTime = 0.0f;
};

