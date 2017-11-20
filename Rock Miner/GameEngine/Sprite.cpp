#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>

namespace SPH {

	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0) {
			glGenBuffers(1, &_vboID); // Generates buffer, inputs: # of buffers, reference to the _vboID bc it will change the ID 
		}

		Vertex vertexData[6];

		// 1st Triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);
		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);
		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		// 2nd Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);
		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);
		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++) {
			vertexData[i].setColor(255, 255, 255, 255);
		}

		vertexData[1].setColor(0, 0, 255, 255);




		glBindBuffer(GL_ARRAY_BUFFER, _vboID); // array buffer is basic vertex buffer and which buffer to use
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // use sizeof to get the size of the vertex array, next input is a pointer to the array, the pointer is implied

		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds buffer, possibly unnecessary?




	}

	void Sprite::draw() {

		glBindTexture(GL_TEXTURE_2D, _texture.id);

		glDrawArrays(GL_TRIANGLES, 0, 6); // Draws data

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinds buffer
	}

}