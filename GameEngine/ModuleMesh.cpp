#include "Application.h"
#include "ModuleMesh.h"
#include "ModuleTextures.h"

#include "HeaderMenu.h"
#include "Transform.h"

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

void Mesh::Render(Tex_Types texture)
{
	//Bind checker texture
	//glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Choose between textures
	switch (texture) {
	case Tex_Types::CURRENT:
		glBindTexture(GL_TEXTURE_2D, textureID);
		break;
	case Tex_Types::CHECKERS:
		glBindTexture(GL_TEXTURE_2D, Application::GetInstance()->textures->testImageID);
		break;
	default:
		glBindTexture(GL_TEXTURE_2D, 0);
		break;
	}
	

	// Binding buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	// Tell OpenGL that array vertex is [ x, y, z, u, v ]
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, (void*)(3 * sizeof(float)));

		// Apply Transform matrix to set Draw offset, then draw 
	glPushMatrix(); // Bind transform matrix
	
	// Apply transform matrix
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr) { //TODO
		glMultMatrixf(&(Application::GetInstance()->hierarchy->selectedGameObj->transform->getMatrix()));
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
}

void ModuleMesh::LoadFile(const char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		//Iterate scene meshes
		for (int i = 0; i < scene->mNumMeshes; i++) {
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
				mesh->vertices[v * VERTEX_ARGUMENTS + 3] = scene->mMeshes[i]->mTextureCoords[0][v].x;
				mesh->vertices[v * VERTEX_ARGUMENTS + 4] = 1- scene->mMeshes[i]->mTextureCoords[0][v].y;	//TODO: be careful INVERTING UVS
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

				//Add mesh to array
				LoadMesh(mesh);
			}
			else {
				//if no faces, just delete mesh
				LOGT(LogsType::WARNINGLOG, "WARNING, loading scene %s, a mesh has no faces.", file_path);
				delete mesh;
			}
		}

		aiReleaseImport(scene);
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

bool ModuleMesh::Init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

update_status ModuleMesh::PostUpdate(float dt)
{
	Tex_Types sendTex = App->textures->selectedTexture;
	
	if (HMenu::isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sendTex = Tex_Types::NONE;
	}
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Render
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->Render(sendTex);
	}

	//FrameBuffer     
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return UPDATE_CONTINUE;
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
