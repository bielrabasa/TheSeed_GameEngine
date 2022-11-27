#include "Primitives.h"
#include "Application.h"
#include "ModuleMesh.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"

GameObject* Primitives::CreatePrimitive(Shapes shape)
{
	GameObject* GO = new GameObject();

	if (shape == Shapes::EMPTY) {
		GO->name = "Empty Object";
		return GO;
	}

	if (shape == Shapes::CAMERA)
	{
		GO->name = "Camera";
		CameraComponent* cc = new CameraComponent();
		GO->AddComponent(cc);
		return GO;
	}

	ComponentMesh* cm = new ComponentMesh();
	Mesh* m = nullptr;

	switch (shape) {
	case Shapes::PLANE:
	{
		GO->name = "Plane";
		m = CreatePlane();
	}
	break;
	case Shapes::CUBE:
	{
		GO->name = "Cube";
		m = CreateCube();
	}
	break;
	case Shapes::SPHERE:
	{
		delete GO;
		GameObject* GO = Application::GetInstance()->meshRenderer->LoadFile("Resources/sphere.fbx");
		GameObject* GOC = GO->childs[0];
		GOC->Free();
		GOC->name = "Sphere";
		delete GO;
		delete cm;
		return GOC;
	}
	break;
	}

	//Somehow, error ocurred
	if (m == nullptr) {
		delete GO;
		LOGT(LogsType::WARNINGLOG, "Error creating primitive, no type selected.");
		return nullptr;
	}

	m->myGameObject = GO;

	//Create AABB box
	m->InitAABB();

	//Add mesh to render pipeline
	Application::GetInstance()->meshRenderer->LoadMesh(m);

	//Add mesh to mesh component of GameObject
	cm->mesh = m;
	GO->AddComponent(cm);

	return GO;
}

Mesh* Primitives::CreateCube()
{
	float s = 0.5f;

	Mesh* mesh = new Mesh();

	//VERTICES
	mesh->num_vertices = 8;
	mesh->vertices = new float[mesh->num_vertices * VERTEX_ARGUMENTS]; //3 floats per vertex

		//generate all vertices
	for (int i = 0; i < (mesh->num_vertices * VERTEX_ARGUMENTS); i++) {
		int p = 1;	//positivity(sign)
		int count = i / VERTEX_ARGUMENTS;
		switch (i % VERTEX_ARGUMENTS) {
		//x
		case 0:
			if (count == 0 || count == 3 || count == 4 || count == 7) p = -1;
		break;
		//y
		case 1:
			if (count == 2 || count == 3 || count == 6 || count == 7) p = -1;
		break;
		//z
		case 2:
			if (count <= 3) p = -1;
		break;
		}

		if ((i % VERTEX_ARGUMENTS) >= 3) {
			mesh->vertices[i] = 0;
		}
		else {
			mesh->vertices[i] = s * p;
		}
	}

	//INDICES
	mesh->num_indices = 36;	//6*2 triangle faces, 3 index per triangle face
	mesh->indices = new uint[mesh->num_indices];

	uint index[36] = 
		{1,3,0,
		1,2,3,
		5,2,1,
		5,6,2,
		4,6,5,
		4,7,6,
		0,7,4,
		0,3,7,
		5,0,4,
		5,1,0,
		2,7,3,
		2,6,7};

	for (int i = 0; i < mesh->num_indices; i++) {
		mesh->indices[i] = index[i];
	}

	return mesh;
}

Mesh* Primitives::CreatePlane()
{
	float s = 0.5;
	
	Mesh* mesh = new Mesh();

	//VERTICES
	mesh->num_vertices = 4;
	mesh->vertices = new float[mesh->num_vertices * VERTEX_ARGUMENTS]; //3 floats per vertex

	//Vertex 0
	//x y z
	mesh->vertices[0] = -s;
	mesh->vertices[1] = 0;
	mesh->vertices[2] = -s;
	//uv
	mesh->vertices[3] = 0;
	mesh->vertices[4] = 0;

	//Vertex 1
	mesh->vertices[5] = s;
	mesh->vertices[6] = 0;
	mesh->vertices[7] = -s;
	mesh->vertices[8] = 1;
	mesh->vertices[9] = 0;

	//Vertex 2
	mesh->vertices[10] = -s;
	mesh->vertices[11] = 0;
	mesh->vertices[12] = s;
	mesh->vertices[13] = 0;
	mesh->vertices[14] = 1;

	//Vertex 3
	mesh->vertices[15] = s;
	mesh->vertices[16] = 0;
	mesh->vertices[17] = s;
	mesh->vertices[18] = 1;
	mesh->vertices[19] = 1;
	

	//INDICES
	mesh->num_indices = 6;	//3* 2 faces
	mesh->indices = new uint[mesh->num_indices];

	mesh->indices[0] = 0;
	mesh->indices[1] = 2;
	mesh->indices[2] = 1;

	mesh->indices[3] = 2;
	mesh->indices[4] = 3;
	mesh->indices[5] = 1;


	return mesh;
}