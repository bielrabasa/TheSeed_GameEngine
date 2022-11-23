#include "Application.h"
#include "Hierarchy.h"
#include "HeaderMenu.h"


HierarchyWindows::HierarchyWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	rootHierarchy = nullptr;

	selectedGameObj = nullptr;
	draggedGameObject = nullptr;
}

HierarchyWindows::~HierarchyWindows()
{
}

bool HierarchyWindows::Init()
{
	rootHierarchy = new GameObject(true);
	rootHierarchy->name = "Scene";

	return true;
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

	//Update all objects
	rootHierarchy->Update();

	if (HMenu::openHierarchy)
	{
		HMenu::ThemeStyleWind();
		HMenu::ThemeStylePopUp();

		ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_NoCollapse);

		PrintHierarchy(rootHierarchy, 0);

		if (openGOOptions)
		{
			openGOOptions = selectedGameObj->MenuOptions();
			if (selectedGameObj->killMe)
			{
				objSelected = false;
				delete selectedGameObj;
				selectedGameObj = nullptr;
			}
		}

		ImGui::End();

		ImGui::PopStyleColor(4);

		if (objSelected)
			selectedGameObj->PrintInspector();

		if (App->input->GetKey(SDL_SCANCODE_DELETE))
		{
			objSelected = false;
			delete selectedGameObj;
			selectedGameObj = nullptr;
		}
	}

	return ret;
}

update_status HierarchyWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void HierarchyWindows::PrintHierarchy(GameObject* GO, int index)
{
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding ;

	bool isNodeOpen;

	if (GO->getParent() == nullptr)
		treeNodeFlags |= ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Bullet;

	else
		treeNodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow;

	if (GO == selectedGameObj)
		treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

	if (!GO->childs.empty())
		isNodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)index, treeNodeFlags, GO->name.c_str(), index);
	
	else
	{
		treeNodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx((void*)(intptr_t)index, treeNodeFlags, GO->name.c_str(), index);
		isNodeOpen = false;
	}

	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("GameObject", GO, sizeof(GameObject*));

		draggedGameObject = GO;

		ImGui::Text(GO->name.c_str()); ImGui::SameLine();
		ImGui::Text(" set as child of "); ImGui::SameLine();
		ImGui::Text(hoveredGameObj->name.c_str());
		
		ImGui::EndDragDropSource();
	}

	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
	{
		hoveredGameObj = GO;

		if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left, true))
		{
			SetGameObjectSelected(GO);
			openGOOptions = false;
		}

		//Menu with obj options
		if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Right))
		{
			SetGameObjectSelected(GO);
			openGOOptions = true;
			ImGui::SetNextWindowPos(ImGui::GetMousePos());
		}
			
	}
	if (ImGui::IsWindowHovered())
	{
		if (!ImGui::IsAnyItemHovered())
		{
			if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
			{
				objSelected = false;
				selectedGameObj = nullptr;
				openGOOptions = false;
			}
		}
	}
	
	

	if (isNodeOpen)
	{
		if (!GO->childs.empty())
		{
			for (int i = 0; i < GO->childs.size(); i++)
			{
				PrintHierarchy(GO->childs[i], i);
			}
		}

		ImGui::TreePop();
	}

	if (ImGui::BeginDragDropTarget()) 
	{
		if (const ImGuiPayload* imGuiPayLoad = ImGui::AcceptDragDropPayload("GameObject"))
		{
			//draggedGameObject->MoveToParent(hoveredGameObj);
			draggedGameObject = nullptr;
		}

		ImGui::EndDragDropTarget();
	}
}

void HierarchyWindows::SetGameObjectSelected(GameObject* GO)
{
	selectedGameObj = GO;
	objSelected = true;
}