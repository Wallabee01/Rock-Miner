#pragma once
#include <GameEngine\IGameScreen.h>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GLSLProgram.h>
#include <GameEngine\Camera2D.h>
#include <GameEngine\GLTexture.h>
#include <GameEngine\Window.h>
#include <GameEngine\DebugRenderer.h>
#include <GameEngine\TileSheet.h>
#include <GameEngine\AudioEngine.h>
#include <GameEngine\SpriteFont.h>

#include "deps\tmxParser\Tmx.h"

#include "Level.h"
#include "Player.h"
#include "Rock.h"
#include "Tree.h"

class GameplayScreen : public SPH::IGameScreen
{
public:
	GameplayScreen(SPH::Window* window);
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPrevScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	void initLevel(int levelIndex);

	virtual void onExit() override;

	virtual void update(float delta) override;
	void updateCollisions(float delta);

	virtual void render() override;
	void renderHUD();

	void tileUnderPlayerCenter();

private:
	void checkInput();

	SPH::GLSLProgram m_textureProgram;
	SPH::Camera2D m_camera;
	SPH::Camera2D m_hudCamera;
	SPH::Camera2D m_bgCamera;
	SPH::GLTexture m_texture;
	SPH::Window* m_window;
	SPH::DebugRenderer m_debugRenderer;
	SPH::TileSheet m_tileSheet1;
	SPH::AudioEngine m_audioEngine;
	SPH::SpriteFont* m_spriteFont;
	SPH::SpriteBatch m_spriteBatch;
	SPH::SpriteBatch m_bgSpriteBatch;
	SPH::SpriteBatch m_hudSpriteBatch;
	SPH::SpriteBatch m_playerSpriteBatch;

	int m_screenWidth;
	int m_screenHeight;

	bool m_renderDebug = true;

	std::vector<Level*> m_levels;
	int m_currentLevel = -1;

	Player* m_player = nullptr;
	std::vector<Agent*> m_agents;
	std::vector<Rock*> m_rocks;
	std::vector<Tree*> m_trees;

	bool m_levelsLoaded = false;

	//Tiled
	Tmx::Map* map;
	const Tmx::Tile* tile;
};

