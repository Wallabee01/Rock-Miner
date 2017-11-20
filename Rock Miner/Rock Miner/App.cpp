#include "App.h"
#include <GameEngine\ScreenList.h>

App::App()
{
}


App::~App()
{
}

void App::onInit()
{

}

void App::addScreens()
{
	m_gameplayScreen = std::make_unique<GameplayScreen>(&m_window);

	m_screenList->addScreen(m_gameplayScreen.get()); //.get() is part of unique_ptr
	m_screenList->setScreen(m_gameplayScreen->getScreenIndex());
}

void App::onExit()
{

}
