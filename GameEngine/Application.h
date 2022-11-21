#pragma once
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleDummy.h"
#include "Hierarchy.h"
#include "ModuleMesh.h"
#include "ModuleTextures.h"

#include "MemLeaks.h"

#include <vector>


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleDummy* dummy;
	HierarchyWindows* hierarchy;
	ModuleMesh* meshRenderer;
	ModuleTextures* textures;

private:

	Timer	ms_timer;
	Timer	game_timer;
	float	dt;
	float	dtG = 0;
	std::vector<Module*> list_modules;

	//Singleton
	Application();
	static Application* app;

public:

	//Singleton
	static Application* GetInstance();

	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	int fpsLimit = 60;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	float GetDTG();
	void SetDTG();
	void StopDTG();
	void PauseDGT();

	int timeSpeed = 1;

};