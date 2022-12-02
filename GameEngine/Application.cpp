#include "Application.h"

Application* Application::app = nullptr;

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	dummy = new ModuleDummy(this);
	hierarchy = new HierarchyWindows(this);
	assets = new AssetsWindows(this);
	meshRenderer = new ModuleMesh(this);
	textures = new ModuleTextures(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	//SDL
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	//Tools
	AddModule(meshRenderer);
	AddModule(textures);
	AddModule(hierarchy);
	AddModule(assets);

	//Scenes
	AddModule(dummy);

	// Renderer last!
	AddModule(renderer3D);
}

Application* Application::GetInstance()
{
	if (app == nullptr)
	{
		app = new Application();
	}
	return app;
}

Application::~Application()
{
	for (int i = list_modules.size() - 1; i >= 0; i--)
	{
		delete list_modules[i];
		list_modules[i] = nullptr;
	}
	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	LOGT(LogsType::SYSTEMLOG, "Application Init --------------");
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		ret = list_modules[i]->Init();
	}
	
	LOGT(LogsType::SYSTEMLOG, "Application Start --------------");
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		ret = list_modules[i]->Start();
	}

	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	//Time management
	if (gameState == GameState::PLAY) dtG = dt * timeSpeed;
	else dtG = 0;
	
	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PreUpdate(dt);
	}

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->Update(dt);
	}

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PostUpdate(dt);
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	
	for(int i = list_modules.size() - 1; i >= 0; i--)
	{
		list_modules[i]->CleanUp();
		delete list_modules[i];
		list_modules[i] = nullptr;
	}
	list_modules.clear();

	return ret;
}

void Application::SetDT(float dt)
{
	this->dt = dt;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

float Application::DTG()
{
	return dtG;
}

bool Application::IsRunning()
{
	return gameState == GameState::PLAY;
}

bool Application::IsPaused()
{
	return gameState == GameState::PAUSE;
}

GameState Application::GetState()
{
	return gameState;
}

void Application::SetState(GameState gameState)
{
	this->gameState = gameState;
}