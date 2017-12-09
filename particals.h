#pragma once
#include <glm.hpp>


struct particals
{
	glm::vec3 position;
	glm::vec3 pointnormal;
	glm::vec2 pointUV;
	glm::vec3 velocity;
	glm::vec3 force;
	float M; //mass
	float IM; // 1.0 / mass 
	bool lock;


}; //reference to particle machanics lecture

