#include "Application.h"
#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(bool enabled)
{
	type = ComponentType::MESH;
	mesh = nullptr;
}

ComponentMesh::~ComponentMesh()
{
	Application::GetInstance()->meshRenderer->DeleteMesh(mesh);
	mesh = nullptr;
}

void ComponentMesh::PrintInspector()
{
}