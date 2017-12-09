#pragma once
#include "glew.h"
#include <glm.hpp>
#include <vector>

class meshd
{
private:

	GLuint VBO;
	std::vector<glm::vec3> vec3data;
	std::vector<glm::vec2> vec2data;



public:

	void genbuffer();

	void AddSinVec2Buffer(glm::vec2 info);
	void AddSinVec3Buffer(glm::vec3 info);

	void addvec2buffer(std::vector<glm::vec2> info);
	void addvec3buffer(std::vector<glm::vec3> info);

	void bufferdatavec3(GLenum use);
	void bufferdatavec2(GLenum use);

	void linkdata(GLuint index, GLint size, GLsizei offset, const GLvoid * startpoint);

	void dynamicbind(std::vector<glm::vec3> info);

	void unbindbuffer();


	void cleanup();



};