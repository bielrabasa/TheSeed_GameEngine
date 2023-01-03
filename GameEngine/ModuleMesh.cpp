#include "Application.h"
#include "ModuleMesh.h"
#include "ModuleTextures.h"

#include "ComponentCamera.h"
#include "HeaderMenu.h"
#include "Transform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "Shader.h"
#include "GameObject.h"


Mesh::~Mesh() {
	delete[] vertices;
	delete[] indices;
	vertices = nullptr;
	indices = nullptr;
	glDeleteBuffers(1, &id_vertices);
	glDeleteBuffers(1, &id_indices);
	id_vertices = 0;
	id_indices = 0;
}

void Mesh::InitAABB()
{
	vector<float3> correctVertex;
	for (size_t i = 0; i < num_vertices * VERTEX_ARGUMENTS; i += VERTEX_ARGUMENTS)
	{
		correctVertex.emplace_back(vertices[i], vertices[i + 1], vertices[i + 2]);
	}
	AABB_box.SetFrom(&correctVertex[0], correctVertex.size());
}

void Mesh::RenderAABB()
{
	float3 corners1[8];
	OBB_box.GetCornerPoints(corners1);

	// Draw
	Application::GetInstance()->renderer3D->DrawBox(corners1, float3(255, 0, 0));

	float3 corners2[8];
	Global_AABB_box.GetCornerPoints(corners2);

	// Draw
	Application::GetInstance()->renderer3D->DrawBox(corners2, float3(0, 0, 255));
}

void Mesh::Render()
{
	if (!myGameObject->isTotalEnabled()) return;

	//Bind checker texture
	//glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);

	//My texture id
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Binding buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	//Bind Shader
	Application::GetInstance()->dummy->shader->BindShader(myGameObject->transform->getGlobalMatrix().ptr());

	// Draw
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	//Unbind Shader
	Application::GetInstance()->dummy->shader->UnbindShader();

	// Unbind buffers
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
}


//
//	MODULE MESH
//

ModuleMesh::ModuleMesh(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	renderedSceneMeshes = 0;
	renderedGameMeshes = 0;
}

GameObject* ModuleMesh::LoadFile(const char* file_path)
{
	uint flags = aiProcess_Triangulate | aiProcess_FlipUVs;
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality | flags);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiMatrix4x4 matrix;
		aiIdentityMatrix4(&matrix);
		GameObject* finalObject = ProcessNode(scene, scene->mRootNode, App->hierarchy->rootHierarchy, file_path, matrix);

		FileInfo info(file_path);
		finalObject->name = info.name;

		aiReleaseImport(scene);

		LOG("File %s loaded!", info.name.c_str());

		finalObject->transform->FlipChildrenYZRotation();
		return finalObject;
	}
	
	LOGT(LogsType::WARNINGLOG, "Error loading scene %s", file_path);
	return nullptr;
}

void ModuleMesh::LoadMesh(Mesh* mesh)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	//Create vertices and indices buffers
	glGenBuffers(1, (GLuint*)&(mesh->id_vertices));
	glGenBuffers(1, (GLuint*)&(mesh->id_indices));

	//Bind and fill buffers
	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertices * VERTEX_ARGUMENTS, mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->num_indices, mesh->indices, GL_STATIC_DRAW);

	//Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);

	//Add mesh to meshes vector
	meshes.push_back(mesh);
}

void ModuleMesh::RenderScene()
{
	renderedSceneMeshes = 0;

	//Render SCENE
	for (int i = 0; i < meshes.size(); i++) {
		if (!App->camera->cam->IsInsideFrustum(meshes[i])) continue;

		meshes[i]->Render();
		if (HMenu::isBoundingBoxes)
			meshes[i]->RenderAABB(); //AABBs

		renderedSceneMeshes++;
	}

	if (!HMenu::isBoundingBoxes) return;
	//Debug Lines

	//Raycast line
	App->renderer3D->DrawLine(debugRaycastA, debugRaycastB, float3(0, 1, 0));

	//Frustum debug
	CameraComponent* c = App->renderer3D->GetMainCamera();
	if (c != nullptr) {
		float3 corners[8];
		c->frustum.GetCornerPoints(corners);
		App->renderer3D->DrawBox(corners, float3(1, 0, 0));
	}
}

void ModuleMesh::RenderGameWindow()
{
	renderedGameMeshes = 0;

	//Render Game Window
	for (int i = 0; i < meshes.size(); i++) {
		if (!App->renderer3D->GetMainCamera()->IsInsideFrustum(meshes[i])) continue;

		meshes[i]->Render();
		renderedGameMeshes++;
	}
}

bool ModuleMesh::Init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

bool ModuleMesh::Start()
{
	return true;
}

bool ModuleMesh::CleanUp()
{
	//Delete Meshes array
	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
		meshes[i] = nullptr;
	}
	meshes.clear();

	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

void ModuleMesh::DeleteMesh(Mesh* m)
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		if (meshes[i] == m) {
			meshes.erase(meshes.begin() + i);
			delete m;
			m = nullptr;
			return;
		}
	}
}

Mesh* ModuleMesh::ImportMesh(aiMesh* aimesh)
{
	Mesh* mesh = new Mesh();

	//Copy fbx mesh info to Mesh struct
	mesh->num_vertices = aimesh->mNumVertices;
	mesh->vertices = new float[mesh->num_vertices * VERTEX_ARGUMENTS]; //3 vertex, uv(x,y)

	for (int v = 0; v < mesh->num_vertices; v++) {
		//vertices
		mesh->vertices[v * VERTEX_ARGUMENTS] = aimesh->mVertices[v].x;
		mesh->vertices[v * VERTEX_ARGUMENTS + 1] = aimesh->mVertices[v].y;
		mesh->vertices[v * VERTEX_ARGUMENTS + 2] = aimesh->mVertices[v].z;

		//uvs
		if (aimesh->mTextureCoords[0] == nullptr) continue;
		mesh->vertices[v * VERTEX_ARGUMENTS + 3] = aimesh->mTextureCoords[0][v].x;
		mesh->vertices[v * VERTEX_ARGUMENTS + 4] = aimesh->mTextureCoords[0][v].y;
	}

	//LOGT(LogsType::SYSTEMLOG, "New mesh with %d vertices", mesh->num_vertices);

	//Load Faces
	if (aimesh->HasFaces())
	{
		//Copy fbx mesh indices info to Mesh struct
		mesh->num_indices = aimesh->mNumFaces * 3;
		mesh->indices = new uint[mesh->num_indices]; // assume each face is a triangle

		//Iterate mesh faces
		for (uint j = 0; j < aimesh->mNumFaces; j++)
		{
			//Check that faces are triangles
			if (aimesh->mFaces[j].mNumIndices != 3) {
				LOGT(LogsType::WARNINGLOG, "WARNING, geometry face with != 3 indices!");
			}
			else {
				memcpy(&mesh->indices[j * 3], aimesh->mFaces[j].mIndices, 3 * sizeof(uint));
			}
		}

		//Create Mesh AABB box
		mesh->InitAABB();

		//Add mesh to array
		LoadMesh(mesh);

		return mesh;
	}
	else {
		//if no faces, just delete mesh
		delete mesh;
		return nullptr;
	}
}

string ModuleMesh::ImportTexture(const aiScene* scene, uint mesh_index, const char* file_path)
{
	//Has a texture
	if (scene->HasMaterials() && scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		//Get texture path
		aiString texture_path;
		scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path);
		scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex]->mProperties[0];
		FileInfo docPath(file_path);
		FileInfo texPath(texture_path.C_Str());

		string finalPath = docPath.path;
		uint assetPos = finalPath.find("Assets/");
		finalPath = finalPath.substr(assetPos, finalPath.find_last_of("/") - assetPos);
		finalPath.append("/").append(texPath.name);

		return finalPath;
	}

	return "";
}

GameObject* ModuleMesh::ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* file_path, aiMatrix4x4 transform)
{
	if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;

	GameObject* GO = new GameObject(parent);
	GO->name = node->mName.C_Str();

	//Transform
	aiMatrix4x4 trmat = node->mTransformation;
	aiVector3D position, scale, rotation;
	aiQuaternion qrot;
	trmat.Decompose(scale, qrot, position);
	rotation = qrot.GetEuler();

	GO->transform->setScale(float3(scale.x, scale.y, scale.z));
	GO->transform->setRotation(float3(rotation.x * RADTODEG, rotation.y * RADTODEG, rotation.z * RADTODEG));
	GO->transform->setPosition(float3(position.x, position.y, position.z));

	//Node has meshes
	if (node->mNumMeshes != 0) 
	{
		//Create Mesh Component
		ComponentMesh* cm = new ComponentMesh();

		//Texture path
		string finalPath = "";

		//Iterate scene meshes
		for (int i = 0; i < node->mNumMeshes; i++) {

			Mesh* mesh = ImportMesh(scene->mMeshes[node->mMeshes[i]]);

			//Mesh has no faces
			if (mesh == nullptr) {
				LOGT(LogsType::WARNINGLOG, "WARNING, loading scene %s, a mesh has no faces.", file_path);
				continue;
			}

			mesh->myGameObject = GO;
			cm->meshes.push_back(mesh);

			if (finalPath == "") finalPath = ImportTexture(scene, node->mMeshes[i], file_path);
		}

		GO->AddComponent(cm);

		//Build component
		if (finalPath != "") {
			ComponentTexture* ct = new ComponentTexture();
			GO->AddComponent(ct);
			ct->SetTexture(finalPath.c_str());
		}
	}

	//Process all children
	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(scene, node->mChildren[i], GO, file_path, trmat);
	}

	return GO;
}
