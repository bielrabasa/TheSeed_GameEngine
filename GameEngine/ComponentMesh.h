#pragma once

#include "Component.h"

struct Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(bool enabled = true);
	~ComponentMesh();

	void Update();
	void PrintInspector();

	vector<Mesh*> meshes;
};