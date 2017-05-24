#include "Arena.h"

const GLfloat arenaData[] = {
	0.0f, 0.9f, 0.0f,
	1.0f, 0.9f, 0.0f,
	1.0f, 1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 0.9f, 0.0f,

	0.0f, 0.9f, 0.0f,
	-1.0f, 0.9f, 0.0f,
	-1.0f, 1.0f, 0.0f,

	0.0f, 0.9f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, -0.9f, 0.0f,
	1.0f, -0.9f, 0.0f,
	1.0f, -1.0f, 0.0f,

	0.0f, -0.9f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, -0.9f, 0.0f,
	-1.0f, -0.9f, 0.0f,
	-1.0f, -1.0f, 0.0f,

	0.0f, -0.9f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	-0.03f, -1.0f, 0.0f,
	0.03f, -1.0f, 0.0f,
	0.03f, 1.0f, 0.0f,

	0.03f, 1.0f, 0.0f,
	-0.03f, 1.0f, 0.0f,
	-0.03f, -1.0f, 0.0f,
};

void Arena::Init() {
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arenaData), arenaData, GL_STATIC_DRAW);
}

void Arena::Render() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 30);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}

Arena::~Arena() {
	if (_VBO != 0) {
		glDeleteBuffers(1, &_VBO);
	}
}