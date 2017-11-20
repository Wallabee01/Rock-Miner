#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <string>

namespace SPH {

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		void swapBuffer();

		int getScreenWidth() { return m_screenWidth; }
		int getScreenHeight() { return m_screenHeight; }
		void setSize(int width, int height, int& screenWidth, int& screenHeight);
		void setFullScreen(int& screenWidth, int& screenHeight);
		void setFullScreenBorderless(int& screenWidth, int& screenHeight); 
		SDL_Window* getWindow() { return m_openGLWindow; }

	private:
		SDL_Window* m_openGLWindow;
		int m_screenWidth;
		int m_screenHeight;


	};

}
