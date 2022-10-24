#include "Primitives.h"
#include "Application.h"
#include "ModuleMesh.h"

Mesh* Primitives::CreateCube()
{
	float s = 0.5f;

	Mesh* mesh = new Mesh();

	//VERTICES
	mesh->num_vertices = 8;
	mesh->vertices = new float[mesh->num_vertices * 3]; //3 floats per vertex

		//generate all vertices
	for (int i = 0; i < (mesh->num_vertices * 3); i++) {
		int p = 1;	//positivity(sign)
		int count = i / 3;
		switch (i % 3) {
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

		mesh->vertices[i] = s * p;
	}

	//INDICES
	mesh->num_indices = 36;	//6*2 triangle faces, 3 index per triangle face
	mesh->indices = new uint[mesh->num_indices];

	uint index[36] = 
		{0,3,1,
		3,2,1,
		1,2,5,
		2,6,5,
		5,6,4,
		6,7,4,
		4,7,0,
		7,3,0,
		4,0,5,
		0,1,5,
		3,7,2,
		7,6,2};

	for (int i = 0; i < mesh->num_indices; i++) {
		mesh->indices[i] = index[i];
	}

	return mesh;
}

Mesh* Primitives::CreateSphere()
{
	Mesh* mesh = new Mesh();


	return mesh;
}

Mesh* Primitives::CreateCylinder()
{
	Mesh* mesh = new Mesh();


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
	mesh->vertices[3] = -1;
	mesh->vertices[4] = -1;

	//Vertex 1
	mesh->vertices[5] = s;
	mesh->vertices[6] = 0;
	mesh->vertices[7] = -s;
	mesh->vertices[8] = 1;
	mesh->vertices[9] = -1;

	//Vertex 2
	mesh->vertices[10] = -s;
	mesh->vertices[11] = 0;
	mesh->vertices[12] = s;
	mesh->vertices[13] = -1;
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