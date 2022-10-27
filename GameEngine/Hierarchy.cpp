#include "Application.h"
#include "Hierarchy.h"


HierarchyWindows::HierarchyWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{

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
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
		gameObjects[i] = nullptr;
	}
	gameObjects.clear();

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

	PrintHierarchy();
	ImGui::End();

	return ret;
}

update_status HierarchyWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void HierarchyWindows::PrintHierarchy()
{

	for (int i = 0; i <= gameObjects.size() - 1; i++)
	{
		if(gameObjects[i]->parent == nullptr)
		{ 
			ImGui::Text(gameObjects[i]->name.c_str());
		}
		else
		{
			int aux = -1;
			aux = gameObjects[i - 1]->childs.size();
			if (aux >= 1)
			{
				for (int j = 0; j <= aux - 1; j++)
				{
					//falta omplir la llista de childs
					ImGui::Text("\t"); ImGui::SameLine();
					ImGui::Text(gameObjects[i - 1]->childs[j]->name.c_str());
					//PrintHierarchy();
				}
			}
		}
	}

}

void HierarchyWindows::AddGameObj(GameObject* GO)
{
	gameObjects.push_back(GO);
}