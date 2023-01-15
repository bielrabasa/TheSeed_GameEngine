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
#include "ButtonComponent.h"

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

	//Canva = Primitives::CreateUIObjects(UIShapes::CANVA);
	//Canva->transform->setScale(float3{ 50,2,50 });
	//Canva->transform->setPosition(float3{ 0,0,10 });
	
	Canva = Primitives::CreateUIObjects(UIShapes::FONS);
	Canva->transform->setScale(float3{ 1300,2,700 });
	Canva->transform->setPosition(float3{ 0,0,10 });

	//Button = Primitives::CreateUIObjects(UIShapes::UIBUTTON);
	//Button->transform->setScale(float3{ 40,0,20 });
	//Button->transform->setPosition(float3{ 0,0,8 });
	
	//Button = Primitives::CreateUIObjects(UIShapes::UIBUTTON);
	//Button->transform->setScale(float3{ 0.6,0,0.4 });
	//Button->transform->setPosition(float3{ 0,1,0 });
	//Button->transform->setRotation(float3{ 0,180,8 });

	InizializatedUI(Canva);

	angle = 0;

	return ret;
}

bool ModuleDummy::CleanUp()
{
	cameraController = nullptr;

	return true;
}

void ModuleDummy::InizializatedUI(GameObject* Canva)
{
	//UIButton First
	ComponentMesh* cm = new ComponentMesh();
	Mesh* m = nullptr;
	GameObject* Button = new GameObject(Canva);
	ComponentTexture* ComText = new ComponentTexture();
	Button->name = "UI Button";
	Button->type = GameObjectType::UI;
	m = Primitives::CreatePlane();
	Button->transform->setScale(float3{ 0.6,0,0.4 });
	Button->transform->setPosition(float3{ 0,1,0 });
	Button->transform->setRotation(float3{ 0,180,8 });
	UIButtonComponent* uibuton = new UIButtonComponent();
	Button->AddComponent(uibuton); //Set texture path
	Button->AddComponent(ComText);
	m->myGameObject = Button;
	m->InitAABB();
	Application::GetInstance()->meshRenderer->LoadMesh(m);
	cm->meshes.push_back(m);
	Button->AddComponent(cm);
	ComText->SetTexture("Assets/Start.png");
	Button->UISType = UIState::DISABLED;

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

		//cameraController->transform->setPosition(float3(cos(angle * DEGTORAD) * -80, 20, sin(angle * DEGTORAD) * -80));
		//cameraController->transform->setRotation(float3(-30, angle - 90, 0));

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
