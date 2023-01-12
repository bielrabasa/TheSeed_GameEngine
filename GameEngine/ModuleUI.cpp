#include "Application.h"
#include "ModuleUI.h"
#include "GameWindow.h"
#include "ModuleMesh.h"
#include "ModuleRenderer3D.h"
#include "ComponentCamera.h"

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

void ModuleUI::BindUIBuffer()
{
	float MousePosX = App->input->GetMouseX();
	float MousePosY = App->input->GetMouseY();
	int widthGWindow = SDL_GetWindowSurface(App->window->window)->w;
	int heightGWindow = SDL_GetWindowSurface(App->window->window)->h;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();


	App->renderer3D->BindCameraBuffer(App->renderer3D->mainGameCamera);
	
	App->renderer3D->mainGameCamera->frustum.pos = float3::zero;
	App->renderer3D->mainGameCamera->frustum.front = float3::unitZ;
	App->renderer3D->mainGameCamera->frustum.up = float3::unitY;
	App->renderer3D->mainGameCamera->frustum.type = OrthographicFrustum;
	App->renderer3D->mainGameCamera->frustum.orthographicHeight = widthGWindow; 
	App->renderer3D->mainGameCamera->frustum.orthographicWidth = heightGWindow; 
	App->renderer3D->mainGameCamera->frustum.nearPlaneDistance = 0.1;
	App->renderer3D->mainGameCamera->frustum.farPlaneDistance = 1000.f;
	App->meshRenderer->RenderUIWindow();

	glEnable(GL_DEPTH_TEST);
	glPopMatrix();


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
