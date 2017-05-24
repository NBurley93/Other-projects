#pragma once
#include <unordered_map>

struct MouseCoordinates {
	int x,y;
};

class InputManager {
public:
	InputManager(void);

	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	void setMouse(int x, int y);
	MouseCoordinates getMouse() { return _mouse; }
private:
	std::unordered_map<unsigned int, bool> _previousKeyMap;
	std::unordered_map<unsigned int, bool> _keyMap;

	bool wasKeyDown(unsigned int keyID);
	MouseCoordinates _mouse;
};