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
#include "AssetsWindow.h"
#include "ModuleUI.h"

#include "MemLeaks.h"

#include <vector>

enum class GameState
{
	PLAY = 0,
	PAUSE = 1,
	STOP = 2
};

class Application
{
public:

	//Singleton
	static Application* GetInstance();

	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void SetDT(float dt);

	float DTG();
	bool IsRunning();
	bool IsPaused();
	bool IsStopped();
	GameState GetState();
	void SetState(GameState gameState);

private:

	//Singleton
	Application();
	static Application* app;
	void AddModule(Module* mod);

public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleDummy* dummy;
	HierarchyWindows* hierarchy;
	AssetsWindows* assets;
	ModuleMesh* meshRenderer;
	ModuleTextures* textures;
	ModuleUI* UI;

	float timeSpeed = 1;
	int fpsLimit = 60;

private:
	float	dt;
	float	dtG;
	GameState gameState = GameState::STOP;

	std::vector<Module*> list_modules;
};