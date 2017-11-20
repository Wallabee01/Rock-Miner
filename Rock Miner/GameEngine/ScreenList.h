#pragma once
#include <vector>

#define SCREEN_INDEX_NO_SCREEN -1

namespace SPH {

	class IGameScreen;
	class IMainGame;

	class ScreenList
	{
	public:
		ScreenList(IMainGame* game);
		~ScreenList();

		IGameScreen* moveNext();
		IGameScreen* movePrev();

		void setScreen(int nextScreen);
		void addScreen(IGameScreen* newScreen);
		void destroy();

		IGameScreen* getCrntScreen();

	protected:
		IMainGame* m_game = nullptr;
		std::vector<IGameScreen*> m_screens;
		int m_crntScreenIndex = SCREEN_INDEX_NO_SCREEN;

	};

}

