#include "Ball.h"
#include <math.h>

const float ballRadius = 0.02f;

Ball::Ball() {
	x = 0.0f;
	y = 0.0f;
	dX = 0.0f;
	dY = 0.0f;
}

void Ball::Update() {
	x += dX;
	y += dY;
}

void Ball::reset() {
	x = 0.0f;
	y = 0.0f;
	dX = -0.01f;
	dY = _initialDx;
}

void Ball::Render() {
	glBegin(GL_TRIANGLES);
		//Triangle 1
		glVertex2f(x - ballRadius, y - ballRadius);
		glVertex2f(x + ballRadius, y - ballRadius);
		glVertex2f(x + ballRadius, y + ballRadius);

		//Triangle 2
		glVertex2f(x - ballRadius, y - ballRadius);
		glVertex2f(x + ballRadius, y + ballRadius);
		glVertex2f(x - ballRadius, y + ballRadius);
	glEnd();
}

void Ball::applyVector(float nX, float nY) {
	dX += nX;
	dY += nY;
	_initialDx = nY;
}

void Ball::flipDx() {
	dX *= -1;

	if (dX < 0) {
		dX -= 0.003;
	}

	if (dX > 0) {
		dX += 0.003;
	}

	if (dY < 0) {
		dY -= 0.003;
	}

	if (dY > 0) {
		dY += 0.003;
	}
}

void Ball::flipDy() {
	dY *= -1;
}