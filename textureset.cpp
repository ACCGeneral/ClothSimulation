#include "textureset.h"

textureset::textureset(std::string textname)
{
	texturename = textname;

}

bool textureset::loadtexture()
{

	image = SDL_LoadBMP(texturename.c_str());
	if (!image)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cout << "Image could not be loaded" << std::endl;
		return false;
	}


	return true;
}

void textureset::gentexture(GLsizei targ)
{
	 glGenTextures(targ, &TextureID);
}

void textureset::twodtexturesetup(bool gamma)
{
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, TextureID);

	// Give the image to OpenGL

	if (gamma)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(image);

}

GLuint textureset::returnID()
{
	return TextureID;
}

void textureset::activatetexture(GLenum textnum)
{
	glActiveTexture(textnum);
	glBindTexture(GL_TEXTURE_2D, TextureID);

}

