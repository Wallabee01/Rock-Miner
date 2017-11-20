#pragma once

namespace SPH {

	class IMainGame;

	enum class ScreenState { NONE, RUNNING, EXIT_APP, CHANGE_NEXT, CHANGE_PREV};

	class IGameScreen
	{
	public:
		friend class ScreenList;

		IGameScreen() {}
		virtual ~IGameScreen() {}

		//Return index of next or prev screen when changing screens
		virtual int getNextScreenIndex() const = 0;
		virtual int getPrevScreenIndex()  const = 0;

		//Called at beg and end of app
		virtual void build() = 0;
		virtual void destroy() = 0;

		//Called when screen enters or exits focus
		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		//Called in main game loop
		virtual void update(float delta) = 0;
		virtual void render() = 0;

		void setRunning() { m_crntState = ScreenState::RUNNING; }

		void setParentGame(IMainGame* game) { m_game = game; }

		int getScreenIndex() const { return m_screenIndex; }

		ScreenState getState() const { return m_crntState; }

	protected:
		IMainGame* m_game = nullptr;
		int m_screenIndex = -1;
		ScreenState m_crntState = ScreenState::NONE;
	};

}

