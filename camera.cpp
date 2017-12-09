#include "camera.h"

camera::camera()
{

	Projection = glm::perspective(glm::radians(53.0f), 4.0f / 3.0f, 0.1f, 100.0f); //this gives me my fov and how far objects will be rendered

	forward = glm::vec3(0, 0, 1);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);

	cameraposition = glm::vec3(-10, 10, -30);


	origdirection = glm::vec3(0, 0, 1);
	newdir = origdirection;
}

void camera::update(float deltaTs, glm::vec3 rotation)
{


	glm::quat quatx = glm::angleAxis((rotation.x), right);

	//rotate the up and forward axis from this new rotation

	up = quatx * up;
	forward = quatx * forward;

	//same for y axis and angle

	glm::quat quaty = glm::angleAxis((rotation.y), up);

	forward = quaty * forward;
	right = quaty * right;

	//same for z axis and angle

	glm::quat quatz = glm::angleAxis((rotation.z), forward);

	up = quatz * up;
	right = quatz * right;

	//periodic re-ortho-normalization is needed to correct our axes

	up = glm::cross(right, forward);
	right = glm::cross(forward, up);
	forward = forward;

	//re-normalize the 3 axes for safe mesure

	up = glm::normalize(up);
	right = glm::normalize(right);
	forward = glm::normalize(forward);

	//create our new rotation from our rotation * xquat * yquat * zquat

	currentrotation = quatz * quaty * quatx * currentrotation;

	//currentrotation = currentrotation * quatx * quaty * quatz;

	newdir = currentrotation * origdirection;

	//newdir = origdirection * currentrotation;

	glm::mat4 RotationMatrix = glm::toMat4(currentrotation);
	glm::mat4 translationmatrix = glm::translate(glm::mat4(1.0f), cameraposition);

	View = glm::inverse(RotationMatrix) * translationmatrix;

	//View = glm::lookAt(cameraposition, glm::vec3(0,0.1,0), up);



}

glm::mat4 camera::returnview()
{
	return View;

}

glm::mat4 camera::returnprojection()
{
	return Projection;

}

void camera::goforward(float deltaTs)
{
	cameraposition = cameraposition + (newdir * 5.0f) * deltaTs;
}

void camera::gobackward(float deltaTs)
{
	cameraposition = cameraposition - (newdir * 5.0f) * deltaTs;

}

glm::vec3 camera::returnmypos()
{
	return cameraposition;
}


