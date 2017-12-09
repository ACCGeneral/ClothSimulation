#pragma once

#include "particals.h"
#include "glm.hpp"
#include "spring.h"
#include <vector>
#include "meshd.h"
#include "VAO.h"
#include "shader.h"
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
#include "triangle.h"
#include "textureset.h"

class cloth
{
private:
	particals points[20][20]; //20x20 grid of particals
	std::vector<springs> Hookes;
	float drag;
	glm::vec3 gravity;

	VAO myVAO;
	meshd vertex;
	meshd normal;
	meshd uvdata;
	shader myshader;
	textureset *mytexture;

	glm::mat4 modelMatrix;

	std::vector<glm::vec3> vertexpoints;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texture;

public:

	cloth();
	void init();
	void glsetup();
	void update(float dt);
	void graphicdataupdate();
	void draw(glm::mat4 & viewMatrix, glm::mat4 & projMatrix, glm::vec3 camerapos);


};