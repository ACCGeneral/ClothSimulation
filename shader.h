#pragma once

#include <glm.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "common.h"

class shader
{

private:

	GLuint program;
	

public:

	shader();
	bool loadshader(std::string shaderlocation, GLenum type);
	void useProgram();
	void stopProgram();
	bool linkcheck();
	void linkshader();
	GLuint returnprogram();
	


};