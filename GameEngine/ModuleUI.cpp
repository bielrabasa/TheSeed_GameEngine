#include "Application.h"
#include "ModuleUI.h"
#include "GameWindow.h"

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

	if (App->gameState == GameState::PLAY)
	{
		
		float MousePosX = App->input->GetMouseX();
		float MousePosY = App->input->GetMouseY();
		int widthGWindow = SDL_GetWindowSurface(App->window->window)->w;
		int heightGWindow = SDL_GetWindowSurface(App->window->window)->h;
		
		float4 GameScreen;
		/*GameScreen = {GameWindows::sizeWindScn.x}
		//float4 GameWindow = App.
		if (MousePosX)
		{

		}*/
	}

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