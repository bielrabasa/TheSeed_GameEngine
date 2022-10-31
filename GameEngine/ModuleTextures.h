#pragma once
#include "Module.h"
#include "glew.h"
#include "il.h"
#include "ilu.h"
#include "ilut.h"

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

	uint LoadTexture(const char* file_path);

private:
	bool Init();
	bool Start();
	bool CleanUp();

public:
	Tex_Types selectedTexture;
	GLuint checkersID;

private:
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4]; // height width rgba

};