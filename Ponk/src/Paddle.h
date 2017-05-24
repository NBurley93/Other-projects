#pragma once
#include "InputManager.h"
#include "Ball.h"
#include <GL/glew.h>

const float _xOffset = 0.05f;
const float _paddleWidth = 0.05f;
const float _paddleHeight = 0.3f;
const float _paddleSpeed = 0.03f;

class Paddle {
public:
	void Init(bool whichPlayer, InputManager& input, bool isAI, int difficultyLevel);
	void Update(Ball& gameBall);
	void Render();

	float X() { return _x; }
	float Y() { return _y; }
private:
	InputManager* _inputPtr;
	bool _whichPlayer;
	bool _isAI;
	int _aiDifficulty;
	float _x, _y;
};