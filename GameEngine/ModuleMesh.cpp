#include "Application.h"
#include "ModuleMesh.h"
#include "ModuleTextures.h"

#include "ComponentCamera.h"
#include "HeaderMenu.h"
#include "Transform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "GameObject.h"


Mesh::~Mesh(){
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

	// Tell OpenGL that array vertex is [ x, y, z, u, v ]
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, (void*)(3 * sizeof(float)));

		// Apply Transform matrix to set Draw offset, then draw 
	glPushMatrix(); // Bind transform matrix
	
	// Apply transform matrix
	if (myGameObject != nullptr) {
		glMultMatrixf(myGameObject->transform->getGlobalMatrix().ptr());
	}

	// Draw
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	glPopMatrix(); // Unbind transform matrix

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
	uint flags = aiProcess_FlipUVs | aiProcess_Triangulate;
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality | flags);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* parentGO = new GameObject();
		//Find last \ or /
		parentGO->name = string(file_path).substr(string(file_path).find_last_of(char(92)) + 1);
		parentGO->name = parentGO->name.substr(string(file_path).find_last_of("/") + 1);
		
		//Iterate scene meshes
		for (int i = 0; i < scene->mNumMeshes; i++) {
			//Create object to store mesh
			GameObject* GO = new GameObject(true);
			parentGO->AddChild(GO);
			GO->name = "Mesh " + to_string(i);

			Mesh* mesh = new Mesh();
			//Copy fbx mesh info to Mesh struct
			mesh->num_vertices = scene->mMeshes[i]->mNumVertices;
			mesh->vertices = new float[mesh->num_vertices * VERTEX_ARGUMENTS]; //3 vertex, uv(x,y)
			
			for (int v = 0; v < mesh->num_vertices; v++) {
				//vertices
				mesh->vertices[v * VERTEX_ARGUMENTS] = scene->mMeshes[i]->mVertices[v].x;
				mesh->vertices[v * VERTEX_ARGUMENTS + 1] = scene->mMeshes[i]->mVertices[v].y;
				mesh->vertices[v * VERTEX_ARGUMENTS + 2] = scene->mMeshes[i]->mVertices[v].z;

				//uvs
				if (scene->mMeshes[i]->mTextureCoords[0] == nullptr) continue;
				mesh->vertices[v * VERTEX_ARGUMENTS + 3] = scene->mMeshes[i]->mTextureCoords[0][v].x;
				mesh->vertices[v * VERTEX_ARGUMENTS + 4] = scene->mMeshes[i]->mTextureCoords[0][v].y;
			}

			LOGT(LogsType::SYSTEMLOG, "New mesh with %d vertices", mesh->num_vertices);

			//Load Faces
			if (scene->mMeshes[i]->HasFaces())
			{
				//Copy fbx mesh indices info to Mesh struct
				mesh->num_indices = scene->mMeshes[i]->mNumFaces * 3;
				mesh->indices = new uint[mesh->num_indices]; // assume each face is a triangle
				
				//Iterate mesh faces
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					//Check that faces are triangles
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
						LOGT(LogsType::WARNINGLOG, "WARNING, geometry face with != 3 indices!");
					}
					else {
						memcpy(&mesh->indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				//Create Mesh AABB box
				mesh->InitAABB();

				//Add mesh to array
				LoadMesh(mesh);

				//Add mesh to GameObject
				ComponentMesh* cm = new ComponentMesh();
				mesh->myGameObject = GO;
				cm->mesh = mesh;
				GO->AddComponent(cm);

				//Has a texture
				if (scene->HasMaterials()) {
					if (scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
						//Get texture path
						aiString texture_path;
						scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path);

						string normTexturePath = texture_path.C_Str();
						string normalisedPath = file_path;
						for (int i = 0; i < normalisedPath.size(); i++)
						{
							if (normalisedPath[i] == '\\')
							{
								normalisedPath[i] = '/';
							}
						}
						for (int i = 0; i < normTexturePath.size(); i++)
						{
							if (normTexturePath[i] == '\\')
							{
								normTexturePath[i] = '/';
							}
						}
						
						string finalPath;
						//normalise folder path
						uint iduint = normalisedPath.find("Assets/") - 1;
						normalisedPath = normalisedPath.substr(normalisedPath.find("Assets/"), normalisedPath.find_last_of("/") - iduint);
						//folder path
						finalPath = normalisedPath;

						//normalise doc path
						normTexturePath = normTexturePath.substr(normTexturePath.find_last_of("/") + 1);
						finalPath.append(normTexturePath);

						//Build component
						ComponentTexture* ct = new ComponentTexture();
						ct->containerParent = GO;
						ct->SetTexture(finalPath.c_str());
						GO->AddComponent(ct);
					}
				}
			}
			else {
				//if no faces, just delete mesh
				LOGT(LogsType::WARNINGLOG, "WARNING, loading scene %s, a mesh has no faces.", file_path);
				delete mesh;
			}
		}

		aiReleaseImport(scene);

		return parentGO;
	}
	else
		LOGT(LogsType::WARNINGLOG, "Error loading scene %s", file_path);

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
			meshes[i]->RenderAABB();

		renderedSceneMeshes++;
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
