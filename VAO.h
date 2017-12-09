#pragma once

#include "glew.h"
#include <glm.hpp>


class VAO
{

private:

	GLuint myVAO;
	int vertexsize;


public:

	VAO();
	void genbuffer(GLsizei n);
	void bindVAO();
	void unbindVAO();
	void setvertexsize(int versize);
	int returnvertexsize();


};