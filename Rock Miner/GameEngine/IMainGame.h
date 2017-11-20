#pragma once
#include "Window.h"
#include "InputManager.h"
#include <memory>

namespace SPH {

	class IGameScreen;
	class ScreenList;

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);
		
		const float getFPS() const { return m_fps; }

		InputManager inputManager;

	protected:
		bool init();
		bool initSystems();

		virtual void update(float delta);
		virtual void render();

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_crntScreen = nullptr;
		bool m_isRunning = false;
		float m_fps = 0.0f;
		Window m_window;
	};
}

