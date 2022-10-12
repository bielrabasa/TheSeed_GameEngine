#include "Inspector.h"
#include "imgui.h"

void InspectorMenu::PrintInspector()
{
	ImGui::Begin("Inspector", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	ImGui::Text("Transform");
	ImGui::Text("Mesh");
	ImGui::Text("Texture");

	ImGui::End();
}