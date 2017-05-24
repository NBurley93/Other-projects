#include "Paddle.h"
#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>

void Paddle::Init(bool whichPlayer, InputManager& input, bool isAI, int difficultyLevel) {
	_whichPlayer = whichPlayer;
	_inputPtr = &input;
	_isAI = isAI;
	_aiDifficulty = difficultyLevel;

	switch (_whichPlayer) {
	case true:
		//Player 1
		_x = (-1.0f) + _xOffset;
		break;

	case false:
		//Player 2
		_x = 1.0f - _xOffset;
		break;
	}
	_y = 0.0f;
	srand(time(0));
}

void Paddle::Update(Ball& gameBall) {
	if (!_isAI) {
		switch (_whichPlayer) {
		case true:
			//Player 1
			if (_inputPtr->isKeyDown(SDLK_w)) {
				//Up p1
				_y += _paddleSpeed;
			}

			if (_inputPtr->isKeyDown(SDLK_s)) {
				//Down p1
				_y -= _paddleSpeed;
			}
			break;

		case false:
			//Player 2
			if (_inputPtr->isKeyDown(SDLK_UP)) {
				//Up p1
				_y += _paddleSpeed;
			}

			if (_inputPtr->isKeyDown(SDLK_DOWN)) {
				//Down p1
				_y -= _paddleSpeed;
			}
			break;
		}
	} else {
		//Calculate hesitation chance
		int hesitationValue = rand() % 100;
		bool willHesitate;

		switch (_aiDifficulty) {
		case 0:
			//EASY
			if (hesitationValue < 55) {
				willHesitate = true;
			}
			break;

		case 1:
			if (hesitationValue < 35) {
				willHesitate = true;
			}
			break;

		case 2:
			if (hesitationValue < 15) {
				willHesitate = true;
			}
			break;

		case 3:
			//BRUTAL
			break;
		}


		if (_aiDifficulty < 3) {
			if (!willHesitate) {
				if (_y < gameBall.Y()) {
					_y += _paddleSpeed;
				}

				if (_y > gameBall.Y()) {
					_y -= _paddleSpeed;
				}
			}
		} else {
			_y = gameBall.Y();
		}
		
	}
}

void Paddle::Render() {
	glBegin(GL_TRIANGLES);
		//Triangle 1
		glVertex2f(_x - (_paddleWidth / 2), _y - (_paddleHeight / 2));
		glVertex2f(_x + (_paddleWidth / 2), _y + (_paddleHeight / 2));
		glVertex2f(_x + (_paddleWidth / 2), _y - (_paddleHeight / 2));

		//Triangle 2
		glVertex2f(_x - (_paddleWidth / 2), _y - (_paddleHeight / 2));
		glVertex2f(_x + (_paddleWidth / 2), _y + (_paddleHeight / 2));
		glVertex2f(_x - (_paddleWidth / 2), _y + (_paddleHeight / 2));
	glEnd();
}