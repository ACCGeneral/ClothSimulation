#include "VAO.h"

VAO::VAO()
{
	myVAO = 0;

}

void VAO::genbuffer(GLsizei n)
{
	glGenVertexArrays(n, &myVAO);
}

void VAO::bindVAO()
{
	glBindVertexArray(myVAO);
}

void VAO::unbindVAO()
{
	glBindVertexArray(0);

}

void VAO::setvertexsize(int versize)
{
	vertexsize = versize;
}

int VAO::returnvertexsize()
{
	return vertexsize;
}

