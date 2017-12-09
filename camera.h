#pragma once

#include <SDL.h>
#include "glew.h"
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <gtc/type_ptr.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/matrix_interpolation.hpp>


class camera
{
private:
	glm::mat4 Projection;
	glm::mat4 View;
	glm::vec3 cameraposition;
	glm::mat4 rotationmatrix;
	glm::mat4 tranlationmatrix;
	glm::quat currentrotation;
	glm::mat4 temp;

	float forwarddis;

	glm::vec3 origdirection;
	glm::vec3 newdir;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;



	glm::mat4 RotationMatrix;

public:
	camera();

	void update(float deltaTs, glm::vec3 rotation);

	glm::mat4 returnview();
	glm::mat4 returnprojection();

	void goforward(float deltaTs);
	void gobackward(float deltaTs);

	glm::vec3 returnmypos();


};