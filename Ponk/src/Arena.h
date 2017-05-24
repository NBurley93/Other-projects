#pragma once
#include <GL/glew.h>

class Arena {
public:
	~Arena();
	void Init();
	void Render();

private:
	GLuint _VBO;
};