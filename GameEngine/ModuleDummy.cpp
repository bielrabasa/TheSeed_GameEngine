#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Logs.h"
#include "HeaderMenu.h"
#include "Config.h"
#include "AssetsWindow.h"
#include "Inspector.h"
#include "Primitives.h"
#include "Transform.h"
#include "ComponentCamera.h"
#include "ComponentShader.h"
#include "ComponentTexture.h"

#include "ComponentMesh.h"

ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	cameraController = nullptr;
	time = nullptr;
}

ModuleDummy::~ModuleDummy()
{
	delete time;
}

bool ModuleDummy::Start()
{
	bool ret = true;

	/*
	GameObject* go = App->meshRenderer->LoadFile("Assets/street/scene.DAE");
	go->transform->setRotation(float3(0, 0, -90));
	*/

	cameraController = Primitives::CreatePrimitive(Shapes::CAMERA);
	cameraController->transform->setPosition(float3(0, 2, -10));
	cameraController->transform->setRotation(float3(0, 0, 0));

	angle = 0;

	//Water Shader
	GameObject* shaderGo = App->meshRenderer->LoadFile("Assets/SubdividedPlane.fbx");
	GameObject* waterGo = shaderGo->childs[0];
	waterGo->Free();
	delete shaderGo;

	ComponentShader* shaderCo = new ComponentShader();
	waterGo->AddComponent(shaderCo);
	shaderCo->ShaderFromFile("Assets/_Shaders/WaterShader.txt");

	waterGo->transform->setRotation(float3(-90.0f, 0.0f, 0.0f));

	time = new float(0.0f);
	shaderCo->shader->AddUniform("time", time, UniformType::f1, 1);

	ComponentTexture* shaderTex = new ComponentTexture();
	waterGo->AddComponent(shaderTex);
	shaderTex->SetTexture("Assets/waterTexture.png");

	return ret;
}

bool ModuleDummy::CleanUp()
{
	cameraController = nullptr;

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if(cameraController->isChildFrom(App->hierarchy->rootHierarchy))
	if (App->IsRunning()) {
		angle += 50 * App->DTG();

		cameraController->transform->setPosition(float3(cos(angle * DEGTORAD) * -80, 20, sin(angle * DEGTORAD) * -80));
		cameraController->transform->setRotation(float3(-30, angle - 90, 0));

		if (angle > 360.0f) angle -= 360.0f;
	}

	*time += dt;
	return ret;
}

update_status ModuleDummy::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	HMenu::ThemeStyleWind();
	HMenu::ThemeStyleMenuBar();
	HMenu::ThemeStylePopUp();
	
	//ImGui::ShowDemoWindow();
	//Print Multiple Windows
	
	//if (HMenu::openAssets)
	//AssetsWindows::PrintAssets();

	if(HMenu::openConsole)
		Logs::PrintDebug();

	if(HMenu::openConig)
		ConfigWindow::PrintConfig(App, dt);

	if (HMenu::openInspector)
		InspectorMenu::PrintInspector();
	
	ImGui::PopStyleColor(6);

	//close the engine
	if (HMenu::quit)
	{
		ret = UPDATE_STOP;
	}

	return ret;
}