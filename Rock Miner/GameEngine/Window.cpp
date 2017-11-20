#include "Window.h"
#include "SPHErrors.h"
#include "wtypes.h"

namespace SPH {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		m_openGLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

		if (m_openGLWindow == nullptr) {
			fatalError("SDL Window could not be created.\n");
		}

		SDL_GLContext glContex = SDL_GL_CreateContext(m_openGLWindow); // Not sure what a context does
		if (glContex == nullptr) {
			fatalError("glContex could not be created.\n");
		}

		GLenum error = glewInit(); // GLenum is a glew function, returns GLEW_OK if initialized;
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew.\n");
		}

		//Check the OpenGL Version
		std::printf("***  OpenGL Version: %s  ***\n", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Sets color

	    //Set VSync
		SDL_GL_SetSwapInterval(0);

		//Enable Alpha Blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		return (0);
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(m_openGLWindow); // Swaps A and B buffer in 1 line of code
	}

	// Get the horizontal and vertical screen sizes in pixel
	void GetDesktopResolution(int& horizontal, int& vertical)
	{
		//requires wtypes.h
		RECT desktop;
		// Get a handle to the desktop window
		const HWND hDesktop = GetDesktopWindow();
		// Get the size of screen to the variable desktop
		GetWindowRect(hDesktop, &desktop);
		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates
		// (horizontal, vertical)
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

	void Window::setFullScreen(int& screenWidth, int& screenHeight) {
		GetDesktopResolution(m_screenWidth, m_screenHeight);
		SDL_SetWindowFullscreen(m_openGLWindow, SDL_WINDOW_FULLSCREEN);

		screenWidth = m_screenWidth;
		screenHeight = m_screenHeight;
	}

	void Window::setFullScreenBorderless(int& screenWidth, int& screenHeight)
	{
		GetDesktopResolution(m_screenWidth, m_screenHeight);
		SDL_SetWindowFullscreen(m_openGLWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

		screenWidth = m_screenWidth;
		screenHeight = m_screenHeight;
	}

	void Window::setSize(int width, int height, int& screenWidth, int& screenHeight)
	{
		m_screenWidth = width; 
		m_screenHeight = height;

		SDL_SetWindowSize(m_openGLWindow, width, height);
		SDL_SetWindowPosition(m_openGLWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		screenWidth = m_screenWidth;
		screenHeight = m_screenHeight;
	}

}