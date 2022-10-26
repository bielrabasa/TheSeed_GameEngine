#pragma once

#include "Module.h"

//ASSIMP
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <string>
using namespace std;

#define VERTEX_ARGUMENTS 5

struct Mesh {
	~Mesh();
	Mesh() {}

	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	void Render();
};

class ModuleMesh : public Module
{
public:
	ModuleMesh(Application* app, bool start_enabled = true);

	void LoadFile(string file_path);
	void LoadMesh(Mesh* mesh);

	update_status PostUpdate(float dt);
	bool Init();
	bool CleanUp();

private:
	vector<Mesh*> meshes;
};