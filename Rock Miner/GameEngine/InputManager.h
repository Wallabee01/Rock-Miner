#pragma once
#include <unordered_map>
#include <glm/glm.hpp>


namespace SPH {

	class InputManager
	{
	public:
		InputManager(): _mouseCoords(0.0f) {}
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);

		void releaseKey(unsigned int keyID);

		bool isKeyDown(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);

		void setMouseCoords(float x, float y);
		glm::vec2 getMouseCoords() const { return _mouseCoords; }

	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> _keyMap; // The key is an unsigned int, and the value is a bool (is the key pressed?)
		std::unordered_map<unsigned int, bool> _prevKeyMap;
		glm::vec2 _mouseCoords;
	};

}