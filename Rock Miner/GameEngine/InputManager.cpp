#include "InputManager.h"

namespace SPH {

	InputManager::~InputManager()
	{
	}

	void InputManager::update() {
		// CPP 11
		for (auto& it : _keyMap) {
			_prevKeyMap[it.first] = it.second;
		}
		
		/*
		for (auto it = _keyMap.begin(); it != _keyMap.end(); it++) {
			_prevKeyMap[it->first] = it->second;
		}
		*/
	}

	void InputManager::pressKey(unsigned int keyID) {
		_keyMap[keyID] = true; // Checks whether keyID is in the map, if not, it will create it, then set it to true
	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}
		return false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		auto it = _prevKeyMap.find(keyID);
		if (it != _prevKeyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}
}