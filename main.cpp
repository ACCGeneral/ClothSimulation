#include <iostream>
#include <SDL.h>
#include "SDL.h"
#include "glew.h"
#include "camera.h"
#include "cloth.h"

bool InitGL()
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "GLEW failed to initialise due to: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}




int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialise" << std::endl;
		return -1;
	}

	// Major version number (4):
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	// Minor version number (3):
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	int winPosX = 0;
	int winPosY = 0;
	int winWidth = 1920;
	int winHeight = 1080;
	SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
	 SDL_WINDOW_OPENGL | SDL_RENDERER_ACCELERATED );

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	camera *mycamera = new camera();

	if (!InitGL())
	{
		return -1;
	}


	glEnable(GL_DEPTH_TEST);

	glm::vec3 currentmouse;

	glm::vec3 rotation;
	int x, y;

	SDL_GetMouseState(&x, &y);
	currentmouse.x = x;
	currentmouse.y = y;
	currentmouse.z = 0;

	float lastTime = SDL_GetTicks();


	cloth *newcloth = new cloth();
	newcloth->init();
	newcloth->glsetup();

	bool forward = false;
	bool backward = false;



	bool go = true;
	while (go)
	{
		rotation.z = 0;
		float current = SDL_GetTicks();
		float deltaTs = (current - lastTime) / 1000.0f;
		lastTime = current;

		SDL_Event incomingEvent;

		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				go = false;
				break;
			case SDL_KEYDOWN:
				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_DOWN:
					backward = true;
					break;
				case SDLK_UP:
					forward = true;
					break;
				case SDLK_a:
					rotation.z = (100.0f) * 0.02f * deltaTs;
					break;
				case SDLK_d:
					rotation.z = -(100.0f) * 0.02f * deltaTs;
					break;
				case SDLK_ESCAPE:
					go = false;
					break;

				}
				break;
				case SDL_KEYUP:
					switch (incomingEvent.key.keysym.sym)
					{
					case SDLK_DOWN:
						backward = false;
						break;
					case SDLK_UP:
						forward = false;
						break;
					}
				break;
			}
		}

		if (backward == true)
		{
			mycamera->gobackward(deltaTs);
		}
		if (forward == true)
		{
			mycamera->goforward(deltaTs);
		}

		SDL_GetMouseState(&x, &y);
		currentmouse.x = x;
		currentmouse.y = y;
		currentmouse.z = 0;

		if (currentmouse.x < 540)
		{
			//rotation.y = -(540 - currentmouse.x) * 0.002f * deltaTs;
		}
		else if (currentmouse.x > 740)
		{
			//rotation.y = -(540 - currentmouse.x) * 0.002f * deltaTs;
		}
		else
		{
			rotation.y = 0.0f;
		}

		if (currentmouse.y > 400)
		{
			//rotation.x = -(currentmouse.y - 400) * 0.005f * deltaTs;
		}
		else if (currentmouse.y < 320)
		{
			//rotation.x = (320 - currentmouse.y) * 0.005f * deltaTs;
		}
		else
		{
			rotation.x = 0.0f;
		}



		mycamera->update(deltaTs, rotation);

		newcloth->update(deltaTs);
		newcloth->graphicdataupdate();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		newcloth->draw(mycamera->returnview(), mycamera->returnprojection(), mycamera->returnmypos());

		SDL_GL_SwapWindow(window);

		if (1000/60 > SDL_GetTicks() - current)	
		{
			SDL_Delay(1000/60 - (SDL_GetTicks()-current));
		}

	}

	delete newcloth;

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
