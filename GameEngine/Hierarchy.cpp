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

	if (!rootHierarchy->childs.empty())
	{
		for (int i = 0; i <= rootHierarchy->childs.size() - 1; i++)
		{
			if (rootHierarchy->childs[i]->parent == nullptr)
			{
				ImGui::Text(rootHierarchy->childs[i]->name.c_str());
			}
			else
			{
				int aux = -1;
				aux = rootHierarchy->childs[i - 1]->childs.size();
				if (aux >= 1)
				{
					for (int j = 0; j <= aux - 1; j++)
					{
						//falta omplir la llista de childs
						ImGui::Text("\t"); ImGui::SameLine();
						ImGui::Text(rootHierarchy->childs[i - 1]->childs[j]->name.c_str());
						//PrintHierarchy();
					}
				}
			}
		}
	}
	else
	{
		ImGui::Text(rootHierarchy->name.c_str());
	}
	

}

void HierarchyWindows::SetGameObjectSelected(GameObject* GO)
{
	gameObjectSelected = GO;
}