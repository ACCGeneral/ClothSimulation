#include "meshd.h"
#include <iostream>

void meshd::genbuffer()
{
	VBO = 0;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void meshd::addvec2buffer(std::vector<glm::vec2> info)
{
	vec2data.insert(vec2data.end(), info.begin(), info.end());
}


void meshd::addvec3buffer(std::vector<glm::vec3> info)
{
	vec3data.insert(vec3data.end(), info.begin(), info.end());
}

void meshd::bufferdatavec3(GLenum use)
{
	glBufferData(GL_ARRAY_BUFFER, vec3data.size() * sizeof(glm::vec3), &vec3data[0], use);

}

void meshd::bufferdatavec2(GLenum use)
{
	glBufferData(GL_ARRAY_BUFFER, vec2data.size() * sizeof(glm::vec2), &vec2data[0], use);

}

void meshd::AddSinVec2Buffer(glm::vec2 info)
{
	vec2data.push_back(info);
}

void meshd::AddSinVec3Buffer(glm::vec3 info)
{
	vec3data.push_back(info);
}

void meshd::linkdata(GLuint index, GLint size, GLsizei offset, const GLvoid * startpoint)
{

	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, startpoint);
	glEnableVertexAttribArray(index);

}

void meshd::dynamicbind(std::vector<glm::vec3> info)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, info.size() * sizeof(glm::vec3), &info[0]);
}

void meshd::unbindbuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void meshd::cleanup()
{
	glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &VAO);


}