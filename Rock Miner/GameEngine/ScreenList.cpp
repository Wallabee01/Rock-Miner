#include "ScreenList.h"
#include "IGameScreen.h"

namespace SPH {

	ScreenList::ScreenList(IMainGame* game) :
		m_game(game)
	{
	}


	ScreenList::~ScreenList()
	{
		destroy();
	}

	SPH::IGameScreen* ScreenList::moveNext()
	{
		IGameScreen* crntScreen = getCrntScreen();
		if (crntScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
			m_crntScreenIndex = crntScreen->getNextScreenIndex();
		}
		return getCrntScreen();
	}

	SPH::IGameScreen* ScreenList::movePrev()
	{
		IGameScreen* crntScreen = getCrntScreen();
		if (crntScreen->getPrevScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
			m_crntScreenIndex = crntScreen->getPrevScreenIndex();
		}
		return getCrntScreen();
	}

	void ScreenList::setScreen(int nextScreen)
	{
		m_crntScreenIndex = nextScreen;
	}

	void ScreenList::addScreen(IGameScreen* newScreen)
	{
		newScreen->m_screenIndex = m_screens.size();
		m_screens.push_back(newScreen);
		newScreen->build();
		newScreen->setParentGame(m_game);
	}

	void ScreenList::destroy()
	{
		for (unsigned int i = 0; i < m_screens.size(); i++) {
			m_screens[i]->destroy(); //Destroys pointers to screens (unique_ptr) in app.cpp
		}
		m_screens.resize(0);
		m_crntScreenIndex = SCREEN_INDEX_NO_SCREEN;
	}

	SPH::IGameScreen* ScreenList::getCrntScreen()
	{
		if (m_crntScreenIndex == SCREEN_INDEX_NO_SCREEN) return nullptr;

		return m_screens[m_crntScreenIndex];
	}

}