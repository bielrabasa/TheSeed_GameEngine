#pragma once
#include "Application.h"
#include "SDL_opengl.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class DevIL_Logic {

public:
	static Application* App;

	static GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4]; // height width rgba
	static GLuint textureID;

	static void Init();

	static void CleanUp();
};