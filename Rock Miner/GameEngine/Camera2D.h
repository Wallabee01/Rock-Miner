#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //Orthographic projection matrix

namespace SPH {

	class Camera2D
	{
	public:
		Camera2D() : _screenWidth(1024), _screenHeight(768), _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f), _scale(1.0f), _reqMatrixUpdate(1) {}
		~Camera2D();

		void init(int screenWidth, int screenHeight);
		void update();

		glm::vec2 screenToWorldCoords(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& pos, const glm::vec2& dimensions);

		//Setters
		void setPosition(glm::vec2& position) { _position = position; _reqMatrixUpdate = true; }
		void setScale(float scale) { _scale = scale; _reqMatrixUpdate = true; }

		//Getters
		glm::vec2 getPosition() { return _position; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }
		float getScale() { return _scale; }

	private:
		int _screenWidth, _screenHeight;
		bool _reqMatrixUpdate;
		float _scale;
		glm::vec2 _position; // Stores 2 elements
		glm::mat4 _cameraMatrix; // Creates a 4x4 Matrix
		glm::mat4 _orthoMatrix;
	};

}