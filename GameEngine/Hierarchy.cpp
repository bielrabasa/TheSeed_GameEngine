#include "Application.h"
#include "Hierarchy.h"


HierarchyWindows::HierarchyWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	rootHierarchy = nullptr;
	rootHierarchy = new GameObject();
	rootHierarchy->name = "Scene";

	gameObjectSelected = nullptr;
}

HierarchyWindows::~HierarchyWindows()
{
}

bool HierarchyWindows::Start()
{
	bool ret = true;

	return ret;
}

bool HierarchyWindows::CleanUp()
{
	delete rootHierarchy;

	return true;
}

update_status HierarchyWindows::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status HierarchyWindows::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_NoCollapse);
	
		PrintHierarchy(rootHierarchy, 0);

	ImGui::End();

	return ret;
}

update_status HierarchyWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void HierarchyWindows::PrintHierarchy(GameObject* GO, int index)
{
	int aux = 0;
	aux = index;
	if(GO->parent == nullptr)
	ImGui::Text(GO->name.c_str());

	if (!GO->childs.empty())
	{
		for (int i = 0; i <= GO->childs.size() - 1; i++)
		{
			for (size_t j = 0; j < aux; j++)
			{
				ImGui::Text("\t"); ImGui::SameLine();
			}
			ImGui::Text("%d", i); ImGui::SameLine();
			ImGui::Text(GO->childs[i]->name.c_str());
			if (!GO->childs[i]->childs.empty())
			{
				aux = aux + 1;
				PrintHierarchy(GO->childs[i], aux);
			}
		}
	}
}


void HierarchyWindows::SetGameObjectSelected(GameObject* GO)
{
	gameObjectSelected = GO;
}