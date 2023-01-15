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
#include "ComponentTexture.h"

#include "ComponentMesh.h"

ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	cameraController = nullptr;
}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;
	GameObject* go = App->meshRenderer->LoadFile("Assets/street/scene.DAE");
	go->transform->setRotation(float3(0, 0, -90));

	cameraController = Primitives::CreatePrimitive(Shapes::CAMERA);
	cameraController->transform->setPosition(float3(0, 4, -20));//10
	cameraController->transform->setRotation(float3(0, 0, 0));

	Canva = Primitives::CreateUIObjects(UIShapes::CANVA);
	Canva->transform->setScale(float3{ 50,2,50 });

	Canva->transform->setPosition(float3{ 0,0,10 });

	ComponentTexture* ct = new ComponentTexture();
	Button = Primitives::CreateUIObjects(UIShapes::UIBUTTON);
	Button->transform->setScale(float3{ 40,0,20 });
	Button->transform->setPosition(float3{ 0,0,8 });
	Button->AddComponent(ct);
	ct->SetTexture("Assets/Start.png");


	angle = 0;

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