#pragma once

#include <iostream>
#include <glm.hpp>

class triangle
{
public:
	glm::vec3 cone;
	glm::vec3 ctwo;
	glm::vec3 cthree;


	glm::vec3 edge1;
	glm::vec3 edge2;


	glm::vec3 normal;


	void calculatenormal();

}; 
