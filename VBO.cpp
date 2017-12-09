#include "VBO.h"

void VBO::genbuffer()
{
	myVBO = 0;

	glGenBuffers(1, &myVBO);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);

}

void VBO::addfloattodata(float info)
{
	data.push_back(info);

}

void VBO::addvectortodata(std::vector<float> addingdata)
{
	data.insert(data.end(), addingdata.begin(), addingdata.end());

}

void VBO::bufferdata(GLenum use)
{
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], use);

}

void VBO::linkdata(GLuint index, GLint size, GLsizei offset, const GLvoid * startpoint)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, startpoint);
	glEnableVertexAttribArray(index);

}

void VBO::unbindbuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void VBO::cleanup()
{
	glDeleteBuffers(1, &myVBO);

}


