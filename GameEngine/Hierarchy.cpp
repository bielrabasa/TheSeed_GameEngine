#include "Application.h"
#include "Hierarchy.h"


HierarchyWindows::HierarchyWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	rootHierarchy = new GameObject();
	rootHierarchy->name = "ROOT";
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

	for (int i = 1; i < GameObjectCopy->size(); i++)
	{
		PrintHierarchy(GameObjectCopy->at(i));
		
	}
	ImGui::End();

	return ret;
}

update_status HierarchyWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void HierarchyWindows::PrintHierarchy(GameObject* GO)
{

	/*for (int i = 0; i <= gameObjects.size() - 1; i++)
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
	}*/

	for (int i = 0; i < GO->childs.size(); i++) {
		StartGameObject(GO->childs[i], i);
	}


}

void HierarchyWindows::AddGameObj(GameObject* GO)
{
	gameObjects.push_back(GO);
}


void HierarchyWindows::StartGameObject(GameObject* gO, int iterations)
{
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	bool openNode;

	if (gO == gameObjectSelected)nodeFlags |= ImGuiTreeNodeFlags_Selected;

	if (gO->childs.empty()) {
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx((void*)(intptr_t)iterations, nodeFlags, gO->name.c_str(), iterations);
		openNode = false;
	}
	else {
		openNode = ImGui::TreeNodeEx((void*)(intptr_t)iterations, nodeFlags, gO->name.c_str(), iterations);
	}

	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("GameObject", gO, sizeof(GameObject*));

		gameObjectDragging = gO;
		ImGui::Text("Change parent of GameObject");
		ImGui::EndDragDropSource();
	}
	if (ImGui::IsItemHovered()) {

		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Left))
			SetGameObjectSelected(gO);

		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right))
			gameObjectRightClick = gO;

	}
	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* imGuiPayLoad = ImGui::AcceptDragDropPayload("GameObject")) {
			gameObjectDragging->AddGameObjectChild(gO);
			gameObjectDragging = nullptr;
		}
		ImGui::EndDragDropTarget();
	}
	if (openNode) {
		if (!gO->childs.empty())
			PrintHierarchy(gO);
		ImGui::TreePop();
	}
}

void HierarchyWindows::SetGameObjectSelected(GameObject* gO)
{
	gameObjectSelected = gO;

}