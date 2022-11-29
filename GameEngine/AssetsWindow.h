#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#pragma comment( lib, "External_Libraries/PhysFS/libx86/physfs.lib" )

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


private:

	void PrintAssets(char* path);
	void PrintAssetsMenu(char* path);

};