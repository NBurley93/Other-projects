#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

enum DIFFICULTY {
	EASY,
	NORMAL,
	HARD,
	BRUTAL
};

void Game::Init() {
	//Get ai difficulty
	std::string useAI = "";

	std::cout << "Do you want to play with two people? (Y or N): ";
	std::cin >> useAI;
	
	bool isUsingAI = false;
	int chosenDifficulty;

	if (useAI == "N") {
		//Prompt to ask difficulty
		isUsingAI = true;

		std::cout << "Select your difficulty" << std::endl <<
			"0 - Easy" << std::endl <<
			"1 - Normal" << std::endl <<
			"2 - Hard" << std::endl <<
			"3 - BRUTAL (YOU WILL NOT SURVIVE)" << std::endl <<
			"Difficulty: ";

		std::cin >> chosenDifficulty;
	}

	_scoreOne = 0;
	_scoreTwo = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL Failure: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	_window = SDL_CreateWindow("Ponk", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_OPENGL);
	_glContext = SDL_GL_CreateContext(_window);
	SDL_GL_MakeCurrent(_window, _glContext);

	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK) {
		std::cout << "GLEW Failure: " << glewGetErrorString(glewErr) << std::endl;
		exit(-1);
	}
	SDL_GL_SetSwapInterval(1);

	_gameState = State::PLAY;

	srand(time(0));
	int directionY = rand() % 2;
	float randomY;

	if (directionY == 0) {
		randomY = 0.007;
	} else {
		randomY = -0.007;
	}

	_gameBall.applyVector(-0.01f, randomY);
	_gameArena.Init();

	_playerOne.Init(true, _input, false, EASY);
	if (isUsingAI) {
		switch (chosenDifficulty) {
		case 0:
			//Easy
			_playerTwo.Init(false, _input, true, EASY);
			break;
		case 1:
			//Normal
			_playerTwo.Init(false, _input, true, NORMAL);
			break;
		case 2:
			//Hard
			_playerTwo.Init(false, _input, true, HARD);
			break;
		case 3:
			//BRUTAL
			_playerTwo.Init(false, _input, true, BRUTAL);
			break;
		}
	} else {
		_playerTwo.Init(false, _input, false, EASY);
	}
}

void Game::Run() {
	while (_gameState != State::EXIT) {
		processUpdate();
		processRender();
	}
	close();
}

void Game::processUpdate() {
	std::string newTitle = "Ponk | Player 1: " + std::to_string(_scoreOne) + " | Player 2: " + std::to_string(_scoreTwo);
	SDL_SetWindowTitle(_window, newTitle.c_str());
	while (SDL_PollEvent(&_gameEvent)) {
		switch (_gameEvent.type) {
		case SDL_QUIT:
			_gameState = State::EXIT;
			break;

		case SDL_KEYDOWN:
			_input.pressKey(_gameEvent.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_input.releaseKey(_gameEvent.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			_input.setMouse(_gameEvent.motion.x, _gameEvent.motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			_input.pressKey(_gameEvent.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			_input.releaseKey(_gameEvent.button.button);
			break;
		}
	}
	_playerOne.Update(_gameBall);
	_playerTwo.Update(_gameBall);
	processInput();
	_gameBall.Update();
}

void Game::processInput() {
	if (_input.isKeyPressed(SDLK_ESCAPE)) {
		_gameState = State::EXIT;
	}

	_input.update();
}

void Game::processRender() {
	glClear(GL_COLOR_BUFFER_BIT);

	//Render here
	_gameBall.Render();
	_gameArena.Render();
	_playerOne.Render();
	_playerTwo.Render();

	//Check ball collision
	if (
	   (_gameBall.X() < _playerOne.X() + (_paddleWidth / 2)) && (_gameBall.Y() < _playerOne.Y() + (_paddleHeight / 2) && _gameBall.Y() > _playerOne.Y() - (_paddleHeight / 2)) ||
	   (_gameBall.X() > _playerTwo.X() - (_paddleWidth / 2)) && (_gameBall.Y() < _playerTwo.Y() + (_paddleHeight / 2) && _gameBall.Y() > _playerTwo.Y() - (_paddleHeight / 2))) {
	    _gameBall.flipDx();
	}

	if (_gameBall.Y() > 0.9 || _gameBall.Y() < -0.9) {
		_gameBall.flipDy();
	}

	if (_gameBall.X() < -1.0f) {
		_scoreTwo++;
		_gameBall.reset();
	}
		
	if (_gameBall.X() > 1.0f) {
		_scoreOne++;
		_gameBall.reset();
	}

	SDL_GL_SwapWindow(_window);
}

void Game::close() {
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}