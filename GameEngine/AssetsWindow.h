#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#pragma comment( lib, "External_Libraries/PhysFS/libx86/physfs.lib" )

#define NEW_FOLDER_PATH "New_Folder/"


class AssetsWindows : public Module
{
public:

	AssetsWindows(Application* app, bool start_enabled = true);
	~AssetsWindows();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void CreateFolder(const char* dir);
	void DeleteFolder(const char* dir);

private:

	void PrintAssets(char* path);
	void PrintAssetsMenu(char* path);

	string pathName = "Assets";

	uint folderTexture;
};