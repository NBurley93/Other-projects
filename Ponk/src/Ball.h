#pragma once
#include <GL/glew.h>

class Ball {
public:
	Ball();
	void Render();
	void Update();

	void applyVector(float nX, float nY);
	float X() { return x; }
	float Y() { return y; }

	void flipDy();
	void flipDx();

	void reset();
private:
	float x, y;
	float dX, dY;
	float _initialDx;
};