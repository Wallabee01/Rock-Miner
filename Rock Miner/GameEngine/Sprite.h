#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>

namespace SPH {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);

		void draw();

	private:
		int _x;
		int _y;
		int _width;
		int _height;
		GLuint _vboID; // Vertex Buffer Object, a GLuint is an unsigned int that is guarenteed 32 bits
		GLTexture _texture;

	};

}