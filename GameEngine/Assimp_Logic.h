#pragma once

#include "Application.h"

//#include "SDL_opengl.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <string>
using namespace std;

struct Mesh {
	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;
};

class Assimp_Logic {
	static vector<Mesh> meshes;
public:
	static Application* App;

	static void LoadFile(string file_path);

	static void Init();

	static void CleanUp();
};