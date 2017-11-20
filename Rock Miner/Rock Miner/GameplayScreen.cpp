#include "GameplayScreen.h"
#include <GameEngine\ScreenList.h>
#include <GameEngine\IMainGame.h>
#include <GameEngine\ResourceManager.h>
#include <GameEngine\SPHErrors.h>

#include <random>
#include <ctime>
#include <iostream>



//Player
const float PLAYER_SPEED = 3.0f;


GameplayScreen::GameplayScreen(SPH::Window* window) :
	m_window(window)
{
}


GameplayScreen::~GameplayScreen()
{
}

int GameplayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPrevScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build()
{
	printf("Build called.\n");
}

void GameplayScreen::destroy()
{
	printf("destroy called.\n");
}

void GameplayScreen::onEntry() // INIT Function
{
	m_window->setSize(800, 600, m_screenWidth, m_screenHeight);

	m_audioEngine.init();

	//Init Camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(1.0f);

	m_hudCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	m_bgCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	//Init spriteBatch
	m_spriteBatch.init();
	m_bgSpriteBatch.init();
	m_hudSpriteBatch.init();
	m_playerSpriteBatch.init();

	//Init sprite font
	m_spriteFont = new SPH::SpriteFont("Fonts/Obelus.ttf", 64); // # is quality

	//Init Debug Renderer
	m_debugRenderer.init();

	//Init shaders
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	//Init Tile sheet
	m_tileSheet1.init(SPH::ResourceManager::getTexture("Textures/master-tileset.png"), glm::ivec2(10, 5));

	//Init TMX Map
	printf("Initializing map.\n");
	map = new Tmx::Map();
	map->ParseFile("Levels/firstMap.tmx");
	printf("Tmx::Map created.\n");
	//printf("Num Image Layers: %d\n", map->GetNumImageLayers());
	printf("Num Layers: %d\n", map->GetNumLayers());
	printf("Num Tilesets: %d\n", map->GetNumTilesets());
	printf("Version #: %f\n", map->GetVersion());
	printf("Tileset Source: %s\n", map->GetTileset(0)->GetImage()->GetSource().c_str());

	tile = map->GetTileset(0)->GetTile(0);
	

	//Player Init
	//m_player = new Player();
	//m_agents.push_back(m_player);

	//Init Level 1
	initLevel(0);

}

void GameplayScreen::initLevel(int levelIndex)
{
	//Load levels into vector once
	if (!m_levelsLoaded) {
		m_levels.push_back(new Level("Levels/level1.txt", m_tileSheet1));
		m_levels.push_back(new Level("Levels/level2.txt", m_tileSheet1));
		m_levelsLoaded = true;
	}

	m_currentLevel = levelIndex;

	//Player Level Init
	m_player->init(m_levels[m_currentLevel]->getPlayerStartPos(), PLAYER_SPEED,
		SPH::ResourceManager::getTexture("Textures/knight84x84reorg.png"), &m_game->inputManager, &m_camera);

	//Init Rocks
	//Clear rock vector
	//for (int i = 0; i < m_rocks.size(); i++) {
	//	m_rocks[i] = m_rocks.back();
	//	m_rocks.pop_back();
	//}

	//m_rocks.resize(0);

	//SPH::GLTexture texture = SPH::ResourceManager::getTexture("Textures/rocky7.png");

	//const std::vector<glm::vec2>& rockPositions = m_levels[m_currentLevel]->getRockStartPos();
	//for (unsigned int i = 0; i < rockPositions.size(); i++) {
	//	m_rocks.push_back(new Rock(rockPositions[i], 1, texture));
	//}

	////Init Trees
	//for (int i = 0; i < m_trees.size(); i++) {
	//	m_trees[i] = m_trees.back();
	//	m_trees.pop_back();
	//}

	//m_trees.resize(0);

	//texture = SPH::ResourceManager::getTexture("Textures/TreeAA1.png");

	//const std::vector<glm::vec2>& treePositions = m_levels[m_currentLevel]->getTreeStartPos();
	//for (unsigned int i = 0; i < treePositions.size(); i++) {
	//	m_trees.push_back(new Tree(treePositions[i], 1, texture));
	//}
}

void GameplayScreen::onExit()
{
	m_debugRenderer.dispose();
	m_bgSpriteBatch.dispose();
	m_spriteBatch.dispose();
}

void GameplayScreen::update(float delta)
{
	//Update keyboard & mouse
	checkInput();

	//Update Player
	m_player->update(delta, m_levels[m_currentLevel]->getLevelData());

	//tileUnderPlayerCenter();

	////Update Rocks
	//for (unsigned int i = 0; i < m_rocks.size(); i++) {
	//	m_rocks[i]->update(delta, m_levels[m_currentLevel]->getLevelData(), m_player);
	//}

	//updateCollisions(delta);

	//Update Camera
	if (m_player != nullptr) {
		m_camera.setPosition(m_player->getPosition());
		m_camera.update();
		m_hudCamera.update();
	}
}

void GameplayScreen::updateCollisions(float delta)
{
	//Update Rock Collision
	for (unsigned int i = 0; i < m_agents.size(); i++) {
		for (unsigned int j = 0; j < m_rocks.size(); j++) {
			m_agents[i]->collideWithEntity(m_rocks[j]);
		}
	}

	//Tree Collision
	for (unsigned int i = 0; i < m_trees.size(); i++) {
		m_player->collideWithTree(m_trees[i]);
	}
}

void GameplayScreen::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.use();

	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Draw background layer
	m_bgSpriteBatch.begin();

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_camera.getPosition().x - m_screenWidth / 2, 
		m_camera.getPosition().y - m_screenHeight / 2, m_screenWidth, m_screenHeight);

	m_bgSpriteBatch.render(destRect, uvRect, SPH::ResourceManager::getTexture("Textures/starry_clouds.png").id,
		1.0f, SPH::Color(255, 255, 255, 255));

	m_bgSpriteBatch.end();
	m_bgSpriteBatch.renderBatch();

	//Draw Level
	m_levels[m_currentLevel]->renderLevel();

	m_spriteBatch.begin();

	//Draw Rocks
	//for (unsigned int i = 0; i < m_rocks.size(); i++) {
	//	m_rocks[i]->render(m_spriteBatch);
	//}

	////Draw Trees
	//for (unsigned int i = 0; i < m_trees.size(); i++) {
	//	m_trees[i]->render(m_spriteBatch);
	//}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_playerSpriteBatch.begin();

	//Draw Player
	m_player->render(m_playerSpriteBatch);

	m_playerSpriteBatch.end();
	m_playerSpriteBatch.renderBatch();

	renderHUD();

	m_textureProgram.unuse();
}

void GameplayScreen::renderHUD() {
	char buffer[256];

	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_hudSpriteBatch.begin();

	const int BUFFER = 10;
	const int SPACING = 55;

	sprintf_s(buffer, "FPS: %.0f", m_game->getFPS());
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(-m_screenWidth / 2 + BUFFER, m_screenHeight / 2 - BUFFER * 2 - SPACING), glm::vec2(1.0), 0.0f, SPH::Color(255, 255, 255, 255) /*SPH::Justification::RIGHT*/);

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();

}

void GameplayScreen::tileUnderPlayerCenter()
{
	glm::vec2 playerCenter = glm::vec2(((m_player->getPosition().x + AGENT_WIDTH / 2.0f) / (float)TILE_WIDTH), 
		                               ((m_player->getPosition().y + AGENT_WIDTH / 2.0f) / (float)TILE_WIDTH));

	char result = m_levels[m_currentLevel]->getLevelData()[playerCenter.y][playerCenter.x];
	switch (result) {
	case '>':
		initLevel(1);
		break;
	case '<':
		initLevel(0);
		break;
	default:
		break;
	}
}

void GameplayScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}
