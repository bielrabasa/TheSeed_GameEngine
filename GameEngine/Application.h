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

#include "MemLeaks.h"

#include <vector>

enum class GameState
{
	PLAY = 0,		//Set the game time
	PAUSE = 1,	//Pause the running game
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

	float timeSpeed = 1;
	int fpsLimit = 60;

private:
	float	dt;
	float	dtG;
	GameState gameState = GameState::STOP;

	std::vector<Module*> list_modules;
};