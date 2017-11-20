#include "Player.h"
#include <SDL.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::init(glm::vec2 position, float speed, SPH::GLTexture texture, SPH::InputManager* inputManager,
	SPH::Camera2D* camera)
{
	m_position = position;
	m_speed = speed;
	m_inputManager = inputManager;
	m_camera = camera;
	m_color = SPH::Color(255, 255, 255, 255);
	m_texture.init(texture, glm::ivec2(6,7));
}

void Player::update(float deltaTime, const std::vector<std::string>& levelData)
{

	if (m_inputManager->isKeyPressed(SDLK_SPACE)) m_isAttacking = true;

	if (m_inputManager->isKeyDown(SDLK_a) && (m_inputManager->isKeyDown(SDLK_s))) {
		m_position.x -= (m_speed / 1.44) * deltaTime; m_position.y -= (m_speed / 1.44) * deltaTime;
		if (m_lastDirection == Direction::LEFT) m_movementDirection = Direction::LEFT;
		else m_movementDirection = Direction::DOWN;
		m_lastDirection = m_movementDirection;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	} 
	else if (m_inputManager->isKeyDown(SDLK_a) && (m_inputManager->isKeyDown(SDLK_w))) {
		m_position.x -= (m_speed / 1.44) * deltaTime; m_position.y += (m_speed / 1.44) * deltaTime;
		if (m_lastDirection == Direction::LEFT) m_movementDirection = Direction::LEFT;
		else m_movementDirection = Direction::UP;
		m_lastDirection = m_movementDirection;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else if (m_inputManager->isKeyDown(SDLK_d) && (m_inputManager->isKeyDown(SDLK_s))) {
		m_position.x += (m_speed / 1.44) * deltaTime; m_position.y -= (m_speed / 1.44) * deltaTime;
		if (m_lastDirection == Direction::RIGHT) m_movementDirection = Direction::RIGHT;
		else m_movementDirection = Direction::DOWN;
		m_lastDirection = m_movementDirection;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else if (m_inputManager->isKeyDown(SDLK_d) && (m_inputManager->isKeyDown(SDLK_w))) {
		m_position.x += (m_speed / 1.44) * deltaTime; m_position.y += (m_speed / 1.44) * deltaTime;
		if (m_lastDirection == Direction::RIGHT) m_movementDirection = Direction::RIGHT;
		else m_movementDirection = Direction::UP;
		m_lastDirection = m_movementDirection;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else if (m_inputManager->isKeyDown(SDLK_a)) {
		m_position.x -= m_speed * deltaTime;
		m_movementDirection = Direction::LEFT;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else if (m_inputManager->isKeyDown(SDLK_d)) {
		m_position.x += m_speed * deltaTime;
		m_movementDirection = Direction::RIGHT;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else if (m_inputManager->isKeyDown(SDLK_s)) {
		m_position.y -= m_speed * deltaTime;
		m_movementDirection = Direction::DOWN;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else if (m_inputManager->isKeyDown(SDLK_w)) {
		m_position.y += m_speed * deltaTime;
		m_movementDirection = Direction::UP;
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::MOVING;
	}
	else {
		if (m_playerState != PlayerState::ATTACKING) m_playerState = PlayerState::IDLE;
	}

	collideWithLevel(levelData);
}

void Player::render(SPH::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x, m_position.y, PLAYER_WIDTH, PLAYER_WIDTH);

	int tileIndex;
	int numTiles;
	float animSpeed = 0.05f;

	if (m_isAttacking) {
		if (m_playerState != PlayerState::ATTACKING) {
			m_playerState = PlayerState::ATTACKING;
			m_animTime = 0.0f;
		}
	}

	switch (m_playerState) {
	case PlayerState::MOVING:
		switch (m_movementDirection) {
		case Direction::DOWN:
			tileIndex = 30;
			numTiles = 5;
			break;
		case Direction::UP:
			tileIndex = 24;
			numTiles = 5;
			break;
		case Direction::LEFT:
			tileIndex = 12;
			numTiles = 6;
			break;
		case Direction::RIGHT:
			tileIndex = 18;
			numTiles = 6;
			break;
		default:
			break;
		}
		break;
	case PlayerState::IDLE: 
		switch (m_movementDirection) {
		case Direction::DOWN:
			tileIndex = 36;
			numTiles = 4;
			break;
		case Direction::UP:
			tileIndex = 9;
			numTiles = 1;
			break;
		case Direction::LEFT:
			tileIndex = 3;
			numTiles = 1;
			break;
		case Direction::RIGHT:
			tileIndex = 0;
			numTiles = 1;
			break;
		default:
			break;
		}
		break;
	case PlayerState::ATTACKING:
		switch (m_movementDirection) {
		case Direction::DOWN:
			tileIndex = 6;
			numTiles = 3;
			break;
		case Direction::UP:
			tileIndex = 9;
			numTiles = 3;
			break;
		case Direction::LEFT:
			tileIndex = 3;
			numTiles = 3;
			break;
		case Direction::RIGHT:
			tileIndex = 0;
			numTiles = 3;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	m_animTime += animSpeed; //add delta to make better

	//Check for attack end
	if (m_animTime > numTiles) {
		m_isAttacking = false;
		m_playerState = PlayerState::IDLE;
	}

	//Apply animation time
	tileIndex = tileIndex + (int)m_animTime % numTiles;

	spriteBatch.render(destRect, m_texture.getUVs(tileIndex), m_texture.texture.id, 0.0f, m_color);
}

bool Player::collideWithTree(Tree* tree)
{
	const float MIN_DISTANCE = AGENT_RADIUS + TREE_COLLISON_RADIUS;

	glm::vec2 centerPosA = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = tree->getPosition() + TREE_COLLISION_OFFSET + glm::vec2(TREE_COLLISON_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
		m_position += collisionDepthVec;
		//entity->m_pos -= collisionDepthVec / 2.0f;
		return true;
	}

	return false;
}
