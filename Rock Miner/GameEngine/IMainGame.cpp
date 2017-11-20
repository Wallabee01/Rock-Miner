#include "IMainGame.h"
#include "IGameScreen.h"
#include "ScreenList.h"
#include "Timing.h"
#include "GameEngine.h"
#include "SPHErrors.h"

#include <algorithm>

namespace SPH {


	IMainGame::IMainGame()
	{
		m_screenList = std::make_unique<ScreenList>(this);
	}

	IMainGame::~IMainGame()
	{

	}

	void IMainGame::run()
	{
		//Program enters here from main
		if (!init()) return;

		m_isRunning = true;

		FPSLimiter limiter;
		limiter.setMaxFPS(120.0f);

		const float DESIRED_FPS = 120.0f;
		const int MAX_PHYSICS_STEPS = 6;
		const float MS_PER_SECOND = 1000.0f;
		const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
		const float MAX_DELTA_TIME = 1.0f;

		float prevTicks = SDL_GetTicks();

		//Program loops here while running
		while (m_isRunning) {
			limiter.begin();

			//Take input
			inputManager.update();

			float newTicks = SDL_GetTicks();
			float frameTime = newTicks - prevTicks;
			prevTicks = newTicks;
			float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

			int i = 0;
			while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
				float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

				//Update game
				update(deltaTime);
				totalDeltaTime -= deltaTime;
				i++;
			}

			//Render updates to buffer
			if (m_isRunning) { //Prevent crash if window is closed in update func
				render();
			}

			//Swap to newly rendered buffer
			m_fps = limiter.end();

			m_window.swapBuffer();
		}
	}

	void IMainGame::exitGame()
	{
		m_crntScreen->onExit();

		if (m_screenList) {
			m_screenList->destroy(); //Call before releasing unique_ptr memory in ~app
			m_screenList.reset(); // unique ptr call to release screen list memory
		}
		m_isRunning = false;
	}

	void IMainGame::onSDLEvent(SDL_Event& evnt)
	{
		switch (evnt.type) {
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(evnt.button.button);
			break;
		default:
			break;
		}
	}

	bool IMainGame::init()
	{
		if (SPH::init()) {
			fatalError("Failed to init SDL");
		}

		initSystems();

		onInit();
		addScreens();

		m_crntScreen = m_screenList->getCrntScreen();
		m_crntScreen->onEntry();
		m_crntScreen->setRunning();

		return true;
	}

	bool IMainGame::initSystems()
	{
		m_window.create("Zombies", 1024, 768, 0);

		return true;
	}

	void IMainGame::update(float delta)
	{
		if (m_crntScreen != nullptr) {
			switch (m_crntScreen->getState()) {
			case ScreenState::RUNNING:
				m_crntScreen->update(delta);
				break;
			case ScreenState::CHANGE_NEXT:
				m_crntScreen->onExit();
				m_crntScreen = m_screenList->moveNext();
				if (m_crntScreen != nullptr) {
					m_crntScreen->setRunning();
					m_crntScreen->onEntry();
				}
				break;
			case ScreenState::CHANGE_PREV:
				m_crntScreen->onExit();
				m_crntScreen = m_screenList->movePrev();
				if (m_crntScreen != nullptr) {
					m_crntScreen->setRunning();
					m_crntScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APP:
				exitGame();
				break;
			default:
				break;

			}
		}
		else {
			exitGame();
		}
	}

	void IMainGame::render()
	{
		glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
		if (m_crntScreen && m_crntScreen->getState() == ScreenState::RUNNING) {
			m_crntScreen->render();
		}
	}
}