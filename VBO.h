#pragma once

#include "glew.h"
#include <glm.hpp>
#include <vector>


class VBO
{

private:
	GLuint myVBO;
	std::vector<float> data;


public:
	void genbuffer();
	void addfloattodata(float info);
	void addvectortodata(std::vector<float> addingdata);

	void bufferdata(GLenum use);

	void linkdata(GLuint index, GLint size, GLsizei offset, const GLvoid * startpoint);
	void unbindbuffer();
	void cleanup();



};