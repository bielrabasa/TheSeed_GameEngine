#include "Application.h"
#include "AssetsWindow.h"
#include "HeaderMenu.h"
#include "PhysFS/include/physfs.h"

AssetsWindows::AssetsWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);
}

AssetsWindows::~AssetsWindows()
{
	PHYSFS_deinit();
}

bool AssetsWindows::Init()
{
	PHYSFS_addToSearchPath("Assets", 1);

	return true;
}

bool AssetsWindows::Start()
{
	bool ret = true;

	return ret;
}

bool AssetsWindows::CleanUp()
{

	return true;
}

update_status AssetsWindows::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status AssetsWindows::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (HMenu::openAssets)
	{
		HMenu::ThemeStyleWind();
		HMenu::ThemeStylePopUp();

		ImGui::Begin("Assets", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginMenuBar())
		{
			PrintAssetsMenu();
			ImGui::EndMenuBar();
		}

		PrintAssets("Assets");

		ImGui::End();

		ImGui::PopStyleColor(4);
	}

	return ret;
}

update_status AssetsWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void AssetsWindows::PrintAssets(char* path)
{
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

	bool isNodeOpen;

	//LOG("%s", PHYSFS_getBaseDir());
	//LOG("%s", PHYSFS_getUserDir());

	//Show the files in this path
	char** rc = PHYSFS_enumerateFiles(path);
	char** i;
	for (i = rc; *i != NULL; i++)
		LOG(" * We've got [%s].\n", *i);

	PHYSFS_freeList(rc);

	//selected file
	//if (GO == selectedGameObj)
	//	treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

	/*if (!GO->childs.empty())
		isNodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)index, treeNodeFlags, GO->name.c_str(), index);

	else
	{
		treeNodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx((void*)(intptr_t)index, treeNodeFlags, GO->name.c_str(), index);
		isNodeOpen = false;
	}

	if (isNodeOpen)
	{
		if (!GO->childs.empty())
		{
			for (int i = 0; i < GO->childs.size(); i++)
			{
				//PrintAssets(GO->childs[i], i);
				PrintAssets(i);
			}
		}

		ImGui::TreePop();
	}*/
}

void AssetsWindows::PrintAssetsMenu()
{
	ImGui::Button("Assets");
	ImGui::Text("->");
}