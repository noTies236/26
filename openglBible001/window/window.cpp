#include "../window/window.h"

SDL_Window* windowAplication::window = 0;

void windowAplication::setupSdl()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "sdl faill";
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("hell", 620, 480, SDL_WINDOW_OPENGL);

	SDL_GL_CreateContext(window);
	
	windowAplication::loadGlad();
}

void windowAplication::loadGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
	}
}	