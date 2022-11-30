#include "Application.h"
#include "ComponentMesh.h"
#include "MathGeoLib.h"
#include "Transform.h"

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

void ComponentMesh::Update()
{
	if (mesh == nullptr) return;
	mesh->OBB_box = mesh->AABB_box;
	mesh->OBB_box.Transform(containerParent->transform->getGlobalMatrix().Transposed());
	mesh->Global_AABB_box.SetNegativeInfinity();
	mesh->Global_AABB_box.Enclose(mesh->OBB_box);
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