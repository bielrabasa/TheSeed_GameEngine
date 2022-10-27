#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Logs.h"
#include "HeaderMenu.h"
#include "Config.h"
#include "Inspector.h"
#include "Primitives.h"


ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;

	App->camera->Position = vec3(1.f, 1.f, 0.0f);
	App->camera->LookAt(vec3(0, 0, 0));

	App->meshRenderer->LoadFile("Assets/BakerHouse.fbx");
	App->meshRenderer->LoadMesh(Primitives::CreatePlane());

	testObject = new GameObject();
	testObject2 = new GameObject();
	testObject3 = new GameObject();
	/*
	App->hierarchy->AddGameObj(testObject);
	App->hierarchy->AddGameObj(testObject2);
	App->hierarchy->AddGameObj(testObject3);*/

	testObject7 = new GameObject();
	testObject8 = new GameObject();
	testObject9 = new GameObject();

	testObject->name = "R";
	testObject2->name = "o";
	testObject3->name = "g";
	/*
	App->hierarchy->AddGameObj(testObject7);
	App->hierarchy->AddGameObj(testObject8);
	App->hierarchy->AddGameObj(testObject9);*/

	testObject7->name = "e";
	testObject8->name = "r";
	testObject9->name = "S";
	
	testObject2->AddGameObjectChild(testObject);
	testObject3->AddGameObjectChild(testObject);
	testObject7->AddGameObjectChild(testObject2);
	//testObject2->parent = testObject;
	//testObject3->parent = testObject;

	return ret;
}

bool ModuleDummy::CleanUp()
{
	LOGT(LogsType::SYSTEMLOG,  "Cleaning test");

	delete testObject;
	delete testObject2;
	delete testObject3;

	delete testObject7;
	delete testObject8;
	delete testObject9;

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;

}

update_status ModuleDummy::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	HMenu::ThemeStyleWind();
	HMenu::ThemeStyleMenuBar();
	HMenu::ThemeStylePopUp();
	
	ImGui::ShowDemoWindow();
	//Print Multiple Windows
	
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