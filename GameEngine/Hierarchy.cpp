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

	PrintHierarchy();

	return ret;
}

update_status HierarchyWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void HierarchyWindows::PrintHierarchy()
{
	ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_NoCollapse);

	for (int i = 0; i < allGameObjects.size(); i++)
	{
		if(allGameObjects.size() !=  NULL && gameObjects[i]->parent == nullptr)
		{ 
			ImGui::Text(gameObjects[i]->name.c_str());
		}
		else
		{
			int aux = -1;
			aux = gameObjects[i]->childs.size();
			if (aux >= 0)
			{
				gameObjects[i]->childs.size();
				for (int j = 0; j <= aux; j++)
				{
					//falta omplir la llista de childs
					ImGui::Text("\tGO");
					//ImGui::Text(gameObjects[i]->childs[j]->name.c_str());
				}
			}
		}
	}

	ImGui::End();
}

void HierarchyWindows::AddGameObj(GameObject* GO)
{

	allGameObjects.push_back(GO);

	if (GO->parent != nullptr)
	{
		GO->parent->childs.push_back(GO);
	}
	else
	{
		gameObjects.push_back(GO);
	}
}
