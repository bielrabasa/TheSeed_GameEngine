#include "ModuleUI.h"
#include "Application.h"
#include "Module.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	return false;
}

update_status ModuleUI::PreUpdate(float dt)
{
	return update_status();
}

update_status ModuleUI::Update(float dt)
{
	return update_status();
}

update_status ModuleUI::PostUpdate(float dt)
{
	return update_status();
}

bool ModuleUI::CleanUp()
{
	return false;
}
