#pragma once
#include "particals.h"

struct springs
{
	particals *A1;
	particals *A2; // the two particals the springs are attached to
	float k; // string coeffinient (will need to be a high number for strong springs otherwise it will drag)
	glm::vec3 X; // extension
	float distance; // needed for k
	float new_distance; //X
	float diff; // needed for X
				//force = X*k;
};