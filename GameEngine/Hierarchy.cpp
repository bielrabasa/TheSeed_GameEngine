#include "Hierarchy.h"
#include "imgui.h"

void HierarchyWindows::PrintHierarchy()
{
	ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	ImGui::Text("GameObject");

	ImGui::End();
}