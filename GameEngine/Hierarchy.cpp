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
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	bool openNode;

	if (!GO->childs.empty())
	{
		/*for (int i = 0; i <= GO->childs.size() - 1; i++)
		{
			if(ImGui::CollapsingHeader(GO->childs[i]->name.c_str()))
			{
				if (!GO->childs[i]->childs.empty())
				{
					aux = aux + 1;
					PrintHierarchy(GO->childs[i], aux);
				}
				else
				{
					aux = aux - 1;
				}
			}
		}*/
		openNode = ImGui::TreeNodeEx((void*)(intptr_t)index, nodeFlags, GO->name.c_str(), index);
	}
	else
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx((void*)(intptr_t)index, nodeFlags, GO->name.c_str(), index);
		openNode = false;
	}
	//}
	if (openNode) {
		if (!GO->childs.empty())
			for (int i = 0; i < GO->childs.size(); i++) {
				PrintHierarchy(GO->childs[i], i);
			}
		ImGui::TreePop();
	}

	if (ImGui::IsItemHovered()) {

		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Left))
			SetGameObjectSelected(GO);

		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right))
			gameObjectRightClick = GO;

	}
}
/*for (size_t j = 0; j < aux; j++)
{
	ImGui::Text("\t"); ImGui::SameLine();
}*/
//ImGui::Text("%d", i); ImGui::SameLine();//ajuda visual per la hierarchy
//ImGui::Text(GO->childs[i]->name.c_str());
//ImGui::ArrowButton(GO->childs[i]->name.c_str(), ImGuiDir_Left);


void HierarchyWindows::SetGameObjectSelected(GameObject* GO)
{
	gameObjectSelected = GO;
}