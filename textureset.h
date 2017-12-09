#pragma once

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"
#include <string>
#include <iostream>


class textureset
{

private:

	GLuint TextureID;
	SDL_Surface * image;

	std::string texturename;

public:

	textureset(std::string textname);
	bool loadtexture();
	void gentexture(GLsizei targ);
	void twodtexturesetup(bool gamma);
	GLuint returnID();
	void activatetexture(GLenum textnum);


};