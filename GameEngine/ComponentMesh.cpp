#include "Application.h"
#include "ComponentMesh.h"
#include "MathGeoLib.h"
#include "Transform.h"

ComponentMesh::ComponentMesh(bool enabled)
{
	type = ComponentType::MESH;
}

ComponentMesh::~ComponentMesh()
{
	for (int i = 0; i < meshes.size(); i++) {
		Application::GetInstance()->meshRenderer->DeleteMesh(meshes[i]);
	}
	meshes.clear();
}

void ComponentMesh::Update()
{

	for (int i = 0; i < meshes.size(); i++) 
	{		
		meshes[i]->OBB_box = meshes[i]->AABB_box;
		meshes[i]->OBB_box.Transform(containerParent->transform->getGlobalMatrix().Transposed());
		meshes[i]->Global_AABB_box.SetNegativeInfinity();
		meshes[i]->Global_AABB_box.Enclose(meshes[i]->OBB_box);
	}
}

void ComponentMesh::PrintInspector()
{
	//Mesh component inspector
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		for (int i = 0; i < meshes.size(); i++) 
		{
			ImGui::LabelText("##%f", "Vertex num (Mesh %d):", i+1);
			ImGui::SameLine();
			ImGui::Text("%d", meshes[i]->num_vertices);
		}
	}
}