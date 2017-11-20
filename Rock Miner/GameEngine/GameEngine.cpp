#include "GameEngine.h"
#include <SDL.h>
#include <GL/glew.h>

namespace SPH {

	int init() {
		SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Creates two buffers, prevents flickering

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		return 0;
	}

}