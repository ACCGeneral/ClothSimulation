#include "triangle.h"

void triangle::calculatenormal()
{
	normal = glm::vec3(0, 0, 0);

	edge1 = cone - ctwo;
	edge2 = cthree - cone;


	normal = glm::normalize(glm::cross(edge1, edge2));

}
