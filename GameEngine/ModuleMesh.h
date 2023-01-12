#pragma once

#include "Module.h"
#include "ModuleTextures.h"

//ASSIMP
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include "MathGeoLib.h"
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

	uint textureID = 0;
	GameObject* myGameObject = nullptr;

	AABB AABB_box;
	OBB OBB_box;
	AABB Global_AABB_box;

	void InitAABB();
	void RenderAABB();
	void Render();
};

class ModuleMesh : public Module
{
public:
	ModuleMesh(Application* app, bool start_enabled = true);

	GameObject* LoadFile(const char* file_path);
	void LoadMesh(Mesh* mesh);

	void RenderScene();
	void RenderGameWindow();
	void RenderUIWindow();

	bool Init();
	bool CleanUp();

	void DeleteMesh(Mesh* m);


	int renderedSceneMeshes;
	int renderedGameMeshes;

	vector<Mesh*> meshes;

	float3 debugRaycastA;
	float3 debugRaycastB;

private:
	Mesh* ImportMesh(aiMesh* aimesh);
	string ImportTexture(const aiScene* scene, uint mesh_index, const char* file_path);
	GameObject* ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* file_path, aiMatrix4x4 transform);
};