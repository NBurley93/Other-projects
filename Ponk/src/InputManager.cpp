#include "InputManager.h"

InputManager::InputManager(void) {
	_mouse.x = 0;
	_mouse.y = 0;
}

void InputManager::update() {
	for (auto it = _keyMap.begin(); it != _keyMap.end(); it++) {
		_previousKeyMap[it->first] = it->second;
	}
}

void InputManager::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
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
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
		return true;
	return false;
}

bool InputManager::wasKeyDown(unsigned int keyID) {
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}

void InputManager::setMouse(int x, int y) {
	_mouse.x = x;
	_mouse.y = y;
}