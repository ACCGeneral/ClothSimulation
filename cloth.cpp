#pragma once

#include "cloth.h"

cloth::cloth()
{
	gravity = glm::vec3(0, -9.8f, 0);
	drag = 1;
	mytexture = new textureset("texture.bmp");
	mytexture->loadtexture();
	mytexture->gentexture(1);
	mytexture->twodtexturesetup(true);
}

void cloth::init()
{
	int xpos = 0, zpos = 0;

	for (int i = 0; i != 20; i++)
	{
		for (int j = 0; j != 20; j++)
		{
			points[i][j].position = glm::vec3(xpos, 0.0, zpos);
			xpos += 1;
			points[i][j].M = 1.4f;
			points[i][j].IM = 1.0f / points[i][j].M;
			points[i][j].lock = false;
			vertexpoints.push_back(points[i][j].position);
			points[i][j].pointUV = glm::vec2(i / 20.0f, j / 20.0f);
		}

		zpos--;
		xpos = 0;
	}  //this will set up the position of each partical in the grid

	for (int i = 0; i != 20; i++)
	{
		for (int j = 0; j != 19; j++)
		{
			springs temp;
			temp.k = 900.0;
			temp.A1 = &points[i][j];
			temp.A2 = &points[i][j + 1];
			Hookes.push_back(temp);
		}
	}  //springs across

	for (int i = 0; i != 20; i++)
	{
		for (int j = 0; j != 19; j++)
		{
			springs temp;
			temp.k = 900.0;
			temp.A1 = &points[j][i];
			temp.A2 = &points[j + 1][i];
			Hookes.push_back(temp);
		}
	}	//springs down

	int i, j;

	for (i = 0, j = 1; i != 19; i++)
	{
		for (int k = 0; k != 19; k++)
		{
			springs temp;
			temp.k = 900.0;
			temp.A1 = &points[i][k + 1];
			temp.A2 = &points[j][k];
			Hookes.push_back(temp);
		}

		j++;
	}
	//springs diagonal (top down)

	for (i = 0, j = 1; i != 19; i++)
	{
		for (int k = 0; k != 19; k++)
		{
			springs temp;
			temp.k = 900.0; //needs to be very strong so it does not drag too far
			temp.A1 = &points[i][k];
			temp.A2 = &points[j][k + 1];
			Hookes.push_back(temp);
		}

		j++;
	} //springs diagonal (down top)

	for (int i = 0; i != Hookes.size(); i++)
	{
		Hookes[i].distance = glm::length(Hookes[i].A2->position - Hookes[i].A1->position); //this will be used to work out the original distance between the 2 ends of the spring 
	}


	int rows = 20;
	int cols = 20;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			if (!(j == cols - 1) && !(i == rows - 1) && !(j == 0) && !(i == 0))
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;
				triangle tri4;
				triangle tri5;
				triangle tri6;

				tri1.cone = points[i - 1][j - 1].position;
				tri1.ctwo = points[i][j - 1].position;
				tri1.cthree = points[i][j].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i - 1][j].position;
				tri2.cthree = points[i - 1][j - 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i - 1][j].position;
				tri3.ctwo = points[i][j].position;
				tri3.cthree = points[i][j + 1].position;
				tri3.calculatenormal();

				tri4.cone = points[i + 1][j + 1].position;
				tri4.ctwo = points[i][j + 1].position;
				tri4.cthree = points[i][j].position;
				tri4.calculatenormal();

				tri5.cone = points[i][j].position;
				tri5.ctwo = points[i + 1][j].position;
				tri5.cthree = points[i + 1][j + 1].position;
				tri5.calculatenormal();

				tri6.cone = points[i + 1][j].position;
				tri6.ctwo = points[i][j].position;
				tri6.cthree = points[i][j - 1].position;
				tri6.calculatenormal();


				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal + tri4.normal + tri5.normal + tri6.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}

			else if (i == 0 && j == 0)
			{
				triangle tri1;
				triangle tri2;

				tri1.cone = points[i][j].position;
				tri1.ctwo = points[i + 1][j].position;
				tri1.cthree = points[i + 1][j + 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i + 1][j + 1].position;
				tri2.ctwo = points[i][j + 1].position;
				tri2.cthree = points[i][j].position;
				tri2.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;


			}
			else if (i == rows - 1 && j == cols - 1)
			{
				triangle tri1;
				triangle tri2;

				tri1.cone = points[i - 1][j - 1].position;
				tri1.ctwo = points[i][j - 1].position;
				tri1.cthree = points[i][j].position;
				tri1.calculatenormal();


				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i - 1][j].position;
				tri2.cthree = points[i - 1][j - 1].position;
				tri2.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}
			else if (i == rows - 1 && j == 0)
			{
				triangle tri1;

				tri1.cone = points[i][j].position;
				tri1.ctwo = points[i - 1][j].position;
				tri1.cthree = points[i][j + 1].position;
				tri1.calculatenormal();

				points[i][j].pointnormal = tri1.normal;

			}
			else if (i == 0 && j == cols - 1)
			{
				triangle tri1;

				tri1.cone = points[i + 1][j].position;
				tri1.ctwo = points[i][j].position;
				tri1.cthree = points[i][j - 1].position;
				tri1.calculatenormal();


				points[i][j].pointnormal = tri1.normal;

			}
			else if (i == 0)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i + 1][j].position;
				tri1.ctwo = points[i][j].position;
				tri1.cthree = points[i][j + 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i + 1][j].position;
				tri2.cthree = points[i + 1][j + 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i + 1][j + 1].position;
				tri3.ctwo = points[i][j + 1].position;
				tri3.cthree = points[i][j].position;
				tri3.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}
			else if (j == 0)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i + 1][j].position;
				tri1.ctwo = points[i][j].position;
				tri1.cthree = points[i][j + 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i + 1][j].position;
				tri2.cthree = points[i + 1][j + 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i + 1][j + 1].position;
				tri3.ctwo = points[i][j + 1].position;
				tri3.cthree = points[i][j].position;
				tri3.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}
			else if (i == rows - 1)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i - 1][j - 1].position;
				tri1.ctwo = points[i][j - 1].position;
				tri1.cthree = points[i][j].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i - 1][j].position;
				tri2.cthree = points[i - 1][j - 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i - 1][j].position;
				tri3.ctwo = points[i][j].position;
				tri3.cthree = points[i][j + 1].position;
				tri3.calculatenormal();


				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;


			}
			else if (j == cols - 1)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i][j].position;
				tri1.ctwo = points[i - 1][j].position;
				tri1.cthree = points[i - 1][j - 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i - 1][j - 1].position;
				tri2.ctwo = points[i][j - 1].position;
				tri2.cthree = points[i][j].position;
				tri2.calculatenormal();

				tri3.cone = points[i + 1][j].position;
				tri3.ctwo = points[i][j].position;
				tri3.cthree = points[i][j - 1].position;
				tri3.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}

		}

	}


	points[0][0].lock = true;
	points[0][19].lock = true;

	std::vector<glm::vec3> vertest;
	std::vector<glm::vec3> nortest;

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			vertest.push_back(points[i][j].position);
			vertest.push_back(points[i+1][j].position);
			vertest.push_back(points[i+1][j+1].position);

			vertest.push_back(points[i][j].position);
			vertest.push_back(points[i][j+1].position);
			vertest.push_back(points[i+1][j+1].position);

			nortest.push_back(points[i][j].pointnormal);
			nortest.push_back(points[i + 1][j].pointnormal);
			nortest.push_back(points[i + 1][j + 1].pointnormal);

			nortest.push_back(points[i][j].pointnormal);
			nortest.push_back(points[i][j + 1].pointnormal);
			nortest.push_back(points[i + 1][j + 1].pointnormal);

			texture.push_back(points[i][j].pointUV);
			texture.push_back(points[i + 1][j].pointUV);
			texture.push_back(points[i + 1][j + 1].pointUV);

			texture.push_back(points[i][j].pointUV);
			texture.push_back(points[i][j + 1].pointUV);
			texture.push_back(points[i + 1][j + 1].pointUV);
		}

	}

	vertexpoints = vertest;
	normals = nortest;

}

void cloth::glsetup()
{
	myVAO.genbuffer(1);
	myVAO.bindVAO();
	vertex.genbuffer();
	vertex.addvec3buffer(vertexpoints);
	vertex.bufferdatavec3(GL_DYNAMIC_DRAW);
	vertex.linkdata(0, 3, 0, 0);

	normal.genbuffer();
	normal.addvec3buffer(normals);
	normal.bufferdatavec3(GL_DYNAMIC_DRAW);
	normal.linkdata(1, 3, 0, 0);

	uvdata.genbuffer();
	uvdata.addvec2buffer(texture);
	uvdata.bufferdatavec2(GL_STATIC_DRAW);
	uvdata.linkdata(2, 2, 0, 0);

	myVAO.setvertexsize(vertexpoints.size());
	myVAO.unbindVAO();


	myshader.loadshader("standeredvertex.txt", GL_VERTEX_SHADER);
	myshader.loadshader("fragmentvector.txt", GL_FRAGMENT_SHADER);
	myshader.linkshader();
	bool linkok = myshader.linkcheck();

	if (linkok == false)
	{
		std::cout << "the cloth shader did not link correctly \n";
	}

}

void cloth::update(float dt)
{
	for (int i = 0; i < Hookes.size(); i++)
	{
		glm::vec3 nd = Hookes[i].A2->position - Hookes[i].A1->position; 
		Hookes[i].new_distance = length(nd); 
		Hookes[i].diff = Hookes[i].new_distance - Hookes[i].distance; 
		Hookes[i].X = glm::normalize(Hookes[i].A2->position - Hookes[i].A1->position) * Hookes[i].diff;

		glm::vec3 temp = Hookes[i].k * Hookes[i].X; 

		Hookes[i].A1->force += temp;
		Hookes[i].A2->force -= temp; // because of newtons 3rd law we must inverse the equation (opposite reaction)
	}


	vertexpoints.clear();

	for (int i = 0; i != 20; i++)
	{
		for (int j = 0; j != 20; j++)
		{
			if (points[i][j].lock != true)
			{
				points[i][j].force += gravity * points[i][j].M;
				points[i][j].force += (-points[i][j].velocity * drag) * points[i][j].M;
				glm::vec3 accel = points[i][j].force / points[i][j].IM;
				points[i][j].force = glm::vec3(0, 0, 0);
				glm::vec3 change = accel * dt;
				points[i][j].velocity += change;
				change = points[i][j].velocity * dt;
				points[i][j].position += change;
			}
			vertexpoints.push_back(points[i][j].position);
		}
	}


	int rows = 20;
	int cols = 20;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			if (!(j == cols - 1) && !(i == rows - 1) && !(j == 0) && !(i == 0))
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;
				triangle tri4;
				triangle tri5;
				triangle tri6;

				tri1.cone = points[i - 1][j - 1].position;
				tri1.ctwo = points[i][j - 1].position;
				tri1.cthree = points[i][j].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i - 1][j].position;
				tri2.cthree = points[i - 1][j - 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i - 1][j].position;
				tri3.ctwo = points[i][j].position;
				tri3.cthree = points[i][j + 1].position;
				tri3.calculatenormal();

				tri4.cone = points[i + 1][j + 1].position;
				tri4.ctwo = points[i][j + 1].position;
				tri4.cthree = points[i][j].position;
				tri4.calculatenormal();

				tri5.cone = points[i][j].position;
				tri5.ctwo = points[i + 1][j].position;
				tri5.cthree = points[i + 1][j + 1].position;
				tri5.calculatenormal();

				tri6.cone = points[i + 1][j].position;
				tri6.ctwo = points[i][j].position;
				tri6.cthree = points[i][j - 1].position;
				tri6.calculatenormal();


				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal + tri4.normal + tri5.normal + tri6.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}

			else if (i == 0 && j == 0)
			{
				triangle tri1;
				triangle tri2;

				tri1.cone = points[i][j].position;
				tri1.ctwo = points[i + 1][j].position;
				tri1.cthree = points[i + 1][j + 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i + 1][j + 1].position;
				tri2.ctwo = points[i][j + 1].position;
				tri2.cthree = points[i][j].position;
				tri2.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;


			}
			else if (i == rows - 1 && j == cols - 1)
			{
				triangle tri1;
				triangle tri2;

				tri1.cone = points[i - 1][j - 1].position;
				tri1.ctwo = points[i][j - 1].position;
				tri1.cthree = points[i][j].position;
				tri1.calculatenormal();


				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i - 1][j].position;
				tri2.cthree = points[i - 1][j - 1].position;
				tri2.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}
			else if (i == rows - 1 && j == 0)
			{
				triangle tri1;

				tri1.cone = points[i][j].position;
				tri1.ctwo = points[i - 1][j].position;
				tri1.cthree = points[i][j + 1].position;
				tri1.calculatenormal();

				points[i][j].pointnormal = tri1.normal;

			}
			else if (i == 0 && j == cols - 1)
			{
				triangle tri1;

				tri1.cone = points[i + 1][j].position;
				tri1.ctwo = points[i][j].position;
				tri1.cthree = points[i][j - 1].position;
				tri1.calculatenormal();


				points[i][j].pointnormal = tri1.normal;

			}
			else if (i == 0)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i + 1][j].position;
				tri1.ctwo = points[i][j].position;
				tri1.cthree = points[i][j + 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i + 1][j].position;
				tri2.cthree = points[i + 1][j + 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i + 1][j + 1].position;
				tri3.ctwo = points[i][j + 1].position;
				tri3.cthree = points[i][j].position;
				tri3.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}
			else if (j == 0)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i + 1][j].position;
				tri1.ctwo = points[i][j].position;
				tri1.cthree = points[i][j + 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i + 1][j].position;
				tri2.cthree = points[i + 1][j + 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i + 1][j + 1].position;
				tri3.ctwo = points[i][j + 1].position;
				tri3.cthree = points[i][j].position;
				tri3.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}
			else if (i == rows - 1)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i - 1][j - 1].position;
				tri1.ctwo = points[i][j - 1].position;
				tri1.cthree = points[i][j].position;
				tri1.calculatenormal();

				tri2.cone = points[i][j].position;
				tri2.ctwo = points[i - 1][j].position;
				tri2.cthree = points[i - 1][j - 1].position;
				tri2.calculatenormal();

				tri3.cone = points[i - 1][j].position;
				tri3.ctwo = points[i][j].position;
				tri3.cthree = points[i][j + 1].position;
				tri3.calculatenormal();


				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;


			}
			else if (j == cols - 1)
			{
				triangle tri1;
				triangle tri2;
				triangle tri3;

				tri1.cone = points[i][j].position;
				tri1.ctwo = points[i - 1][j].position;
				tri1.cthree = points[i - 1][j - 1].position;
				tri1.calculatenormal();

				tri2.cone = points[i - 1][j - 1].position;
				tri2.ctwo = points[i][j - 1].position;
				tri2.cthree = points[i][j].position;
				tri2.calculatenormal();

				tri3.cone = points[i + 1][j].position;
				tri3.ctwo = points[i][j].position;
				tri3.cthree = points[i][j - 1].position;
				tri3.calculatenormal();

				points[i][j].pointnormal = glm::normalize(tri1.normal + tri2.normal + tri3.normal);
				points[i][j].pointnormal.y = -points[i][j].pointnormal.y;

			}

		}

	}


	std::vector<glm::vec3> vertest;
	std::vector<glm::vec3> nortest;


	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			vertest.push_back(points[i][j].position);
			vertest.push_back(points[i + 1][j].position);
			vertest.push_back(points[i + 1][j + 1].position);

			vertest.push_back(points[i][j].position);
			vertest.push_back(points[i][j + 1].position);
			vertest.push_back(points[i + 1][j + 1].position);

			nortest.push_back(points[i][j].pointnormal);
			nortest.push_back(points[i + 1][j].pointnormal);
			nortest.push_back(points[i + 1][j + 1].pointnormal);

			nortest.push_back(points[i][j].pointnormal);
			nortest.push_back(points[i][j + 1].pointnormal);
			nortest.push_back(points[i + 1][j + 1].pointnormal);
		}

	}

	vertexpoints = vertest;
	normals = nortest;

	glm::mat4 transposematrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-10));
	modelMatrix = transposematrix;

}

void cloth::graphicdataupdate()
{

	vertex.dynamicbind(vertexpoints);
	myVAO.setvertexsize(vertexpoints.size());

	normal.dynamicbind(normals);
}

void cloth::draw(glm::mat4 & viewMatrix, glm::mat4 & projMatrix, glm::vec3 camerapos)
{
	myshader.useProgram();
	myVAO.bindVAO();

	glUniformMatrix4fv(glGetUniformLocation(myshader.returnprogram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myshader.returnprogram(), "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myshader.returnprogram(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMatrix));

	glUniform3f(glGetUniformLocation(myshader.returnprogram(), "camerapos"), camerapos.x,camerapos.y,camerapos.z);
	glUniform1f(glGetUniformLocation(myshader.returnprogram(), "shine"), 32);
	glUniform1f(glGetUniformLocation(myshader.returnprogram(), "strength"), 1);

	glUniform3f(glGetUniformLocation(myshader.returnprogram(), "mydirlight.direction"), 0.0f,0.0f,1.0f);
	glUniform3f(glGetUniformLocation(myshader.returnprogram(), "mydirlight.ambient"), 0.1f,0.1f,0.1f);
	glUniform3f(glGetUniformLocation(myshader.returnprogram(), "mydirlight.lightcolour"),1.0f,1.0f,1.0f);

	glUniform1i(glGetUniformLocation(myshader.returnprogram(), "gamma"), true);
	mytexture->activatetexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(myshader.returnprogram(), "myTextureSampler"), 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, myVAO.returnvertexsize());

	myVAO.unbindVAO();
	myshader.stopProgram();
}

