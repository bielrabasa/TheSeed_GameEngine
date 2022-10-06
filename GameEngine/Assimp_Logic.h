#pragma once

#include "Application.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <string>
using namespace std;

struct Mesh {
	~Mesh() {
		delete[num_vertices] vertices;
		delete[num_indices] indices;
	}
	Mesh() {}

	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	void Render();
};

class Assimp_Logic {
	static vector<Mesh*> meshes;

public:
	static void LoadFile(string file_path);
	static void LoadMesh(Mesh* mesh);
	static void Render();
	static void Init();
	static void CleanUp();
};