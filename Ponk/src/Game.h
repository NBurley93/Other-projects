#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "InputManager.h"
#include "Arena.h"
#include "Ball.h"
#include "Paddle.h"

enum class State {
	PLAY,
	EXIT
};

class Game {
public:
	void Init();
	void Run();
private:
	void processUpdate();
	void processRender();
	void processInput();
	void close();

	SDL_Window* _window;
	SDL_GLContext _glContext;

	State _gameState;
	SDL_Event _gameEvent;
	InputManager _input;
	Arena _gameArena;
	Ball _gameBall;
	Paddle _playerOne, _playerTwo;

	unsigned int _scoreOne, _scoreTwo;
};