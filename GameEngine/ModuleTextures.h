#pragma once
#include "Module.h"
#include "glew.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

enum class Tex_Types{
	NONE,
	CHECKERS,
	CURRENT,
};

class ModuleTextures : public Module
{
public:

	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures() {}

	bool Start();
	bool CleanUp();

	Tex_Types selectedTexture;
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4]; // height width rgba
	GLuint checkersID;
};