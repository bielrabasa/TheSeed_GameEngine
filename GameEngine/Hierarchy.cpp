#include "Hierarchy.h"
#include "imgui.h"

void HierarchyWindows::PrintHierarchy()
{
	ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_MenuBar);

	ImGui::Text("GameObject");

	ImGui::End();
}