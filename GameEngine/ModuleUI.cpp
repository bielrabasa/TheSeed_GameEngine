#include "Application.h"
#include "ModuleUI.h"

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
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status ModuleUI::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status ModuleUI::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	return ret;
}

bool ModuleUI::CleanUp()
{
	return false;
}