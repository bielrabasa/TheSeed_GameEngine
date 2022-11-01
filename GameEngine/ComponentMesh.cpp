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
	//Mesh component inspector
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::LabelText("##%f", "Number of vertex:");
		ImGui::SameLine();
		if (mesh == nullptr) return;
		ImGui::Text("%d", mesh->num_vertices);
	}
}