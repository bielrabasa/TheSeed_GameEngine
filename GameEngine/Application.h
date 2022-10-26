#pragma once
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleDummy.h"
#include "ModuleMesh.h"

#include <vector>


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleDummy* dummy;
	ModuleMesh* meshRenderer;

private:

	Timer	ms_timer;
	float	dt;
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

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};