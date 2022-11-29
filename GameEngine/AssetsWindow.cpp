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
			PrintAssetsMenu((char*)pathName.c_str());
			ImGui::EndMenuBar();
		}

		PrintAssets((char*)pathName.c_str());

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
	//LOG("%s", PHYSFS_getBaseDir());
	//LOG("%s", PHYSFS_getUserDir());

	//Show the files in this path
	char** rc = PHYSFS_enumerateFiles(path);
	char** i;
	for (i = rc; *i != NULL; i++)
	{
		string pName = *i;

		if (pName.find(".") != -1)
		{
			ImGui::Text(*i);
		}
		else
		{
			if (ImGui::Button(*i))
			{
				pathName.append("/");
				pathName.append(*i);
				PrintAssets((char*)pathName.c_str());
			}
		}
	}
		//LOG(" * We've got [%s].\n", *i);

	PHYSFS_freeList(rc);
}

void AssetsWindows::PrintAssetsMenu(char* path)
{
	string pName = path;
	string pRelative = pName.substr(0, pName.find_first_of("/"));


	char comprobar = '/';

	for (size_t i = 0; i < sizeof(path); i++)
	{
		//pName.append((char*)path[i]);

		if (pName.find("/") != -1)
		{
			if (ImGui::Button((char*)pName.c_str()))
			{
				pathName = pRelative;
			}

			ImGui::Text("->");

		}
	}

}