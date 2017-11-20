#include "Camera2D.h"

namespace SPH {

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update() {

		if (_reqMatrixUpdate) { // We are going to translate by the negative position, so when we go right, the scene goes left
			
			//Camera Translation
			glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//Scale Translation
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_reqMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::screenToWorldCoords(glm::vec2 screenCoords) {
		//Invert y coords
		screenCoords.y = _screenHeight - screenCoords.y;
		// Make it so 0,0 is the center of the screen
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		// Scale the coords
		screenCoords /= _scale;
		// Translate with the camera pos
		screenCoords += _position;

		return screenCoords;
	}

	bool Camera2D::isBoxInView(const glm::vec2& pos, const glm::vec2& dimensions) {

		glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / _scale;
		
		const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;


	glm::vec2 centerPos = pos + dimensions / 2.0f;
	glm::vec2 centerCameraPos = _position;
	glm::vec2 distVec = centerPos - centerCameraPos;

	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	if (xDepth > 0 && yDepth > 0) {
		return true;
		}
	return false;
	}
}

