#pragma once

#include "Application.h"

//#include "SDL_opengl.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <string>
using namespace std;

struct Mesh {
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;
};

class Assimp_Logic {

public:
	static Application* App;

	static void LoadFile(string file_path);

	static void Init();

	static void CleanUp();
};