#include <iostream>
#include "SDL3/SDL.h"   
#include "glad/glad.h"

#ifndef WINDOW_H
#define	WINDOW_H
	extern bool isRunning;
#endif

namespace windowAplication {
	extern SDL_Window* window;
	void setupSdl();
	void loadGlad();
}