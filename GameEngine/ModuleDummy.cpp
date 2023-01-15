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
#include "FonsUIComponent.h"
#include "CheckBoxComponent.h"

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


	//Canva = Primitives::CreateUIObjects(UIShapes::CANVA);
	//Canva->transform->setScale(float3{ 50,2,50 });
	//Canva->transform->setPosition(float3{ 0,0,10 });
	 


	//Button = Primitives::CreateUIObjects(UIShapes::UIBUTTON);
	//Button->transform->setScale(float3{ 40,0,20 });
	//Button->transform->setPosition(float3{ 0,0,8 });
	
	//Button = Primitives::CreateUIObjects(UIShapes::UIBUTTON);
	//Button->transform->setScale(float3{ 0.6,0,0.4 });
	//Button->transform->setPosition(float3{ 0,1,0 });
	//Button->transform->setRotation(float3{ 0,180,8 });

	InizializatedUI(Canva);
	InizializatedConfig(Canva);
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

	ComponentMesh* MeshFons = new ComponentMesh();
	Mesh* mFons = nullptr;
	Fons = new GameObject(Canva);
	ComponentTexture* ComTextFons = new ComponentTexture();
	Fons->name = "BackGround";
	Fons->type = GameObjectType::UI;
	mFons = Primitives::CreatePlane();
	Fons->transform->setRotation(float3{ 0,180,8 });
	FonsComponent* Fonscomp = new FonsComponent();
	Fons->AddComponent(Fonscomp); //Set texture path
	Fons->AddComponent(ComTextFons);
	mFons->myGameObject = Fons;
	mFons->InitAABB();
	Application::GetInstance()->meshRenderer->LoadMesh(mFons);
	MeshFons->meshes.push_back(mFons);
	Fons->AddComponent(MeshFons);
	ComTextFons->SetTexture("Assets/Start_Menu.png");
	Fons->UISType = UIState::DISABLED;

	//UIButton First
	ComponentMesh* cm = new ComponentMesh();
	Mesh* m = nullptr;
	GameObject* Button = new GameObject(Fons);
	ComponentTexture* ComText = new ComponentTexture();
	Button->name = "UI Button";
	Button->type = GameObjectType::UI;
	m = Primitives::CreatePlane();
	Button->transform->setScale(float3{ 0.6,0,0.4 });
	Button->transform->setPosition(float3{ 0.15,1,0 });
	Button->transform->setRotation(float3{ 0,0,8 });
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
	Button->StartButton = true;
}

void ModuleDummy::InizializatedConfig(GameObject* Canva)
{
	//Create Options Window Fons
	F1_Screen = new GameObject(Canva);
	ComponentMesh* Fonscm = new ComponentMesh();
	Mesh* Fonsm = nullptr;
	FonsComponent* FonsComp = new FonsComponent();
	ComponentTexture* FonsComText = new ComponentTexture();
	F1_Screen->name = "Options";
	F1_Screen->type = GameObjectType::UI;
	Fonsm = Primitives::CreatePlane();
	F1_Screen->transform->setRotation(float3{ 0,180,8 });
	F1_Screen->AddComponent(FonsComp); //Set texture path
	F1_Screen->AddComponent(FonsComText);
	Fonsm->myGameObject = F1_Screen;
	Fonsm->InitAABB();
	Application::GetInstance()->meshRenderer->LoadMesh(Fonsm);
	Fonscm->meshes.push_back(Fonsm);
	F1_Screen->AddComponent(Fonscm);
	FonsComText->SetTexture("Assets/Options_Menu.png");
	F1_Screen->UISType = UIState::DISABLED;
	F1_Screen->isEnabled = false;

	Vsync_Obj = new GameObject(F1_Screen);
	ComponentMesh* Vsynccm = new ComponentMesh();
	Mesh* Vsyncm = nullptr;
	CheckBoxComponent* VsyncComp = new CheckBoxComponent();
	ComponentTexture* VsyncText = new ComponentTexture();
	Vsync_Obj->name = "Vsync";
	Vsync_Obj->type = GameObjectType::UI;
	Vsyncm = Primitives::CreatePlane();
	Vsync_Obj->transform->setPosition(float3{ 0.2,1,0 });
	Vsync_Obj->transform->setScale(float3{ 0.1,0,0.2 });
	Vsync_Obj->transform->setRotation(float3{ 0,0,8 });
	Vsync_Obj->AddComponent(VsyncComp); //Set texture path
	Vsync_Obj->AddComponent(VsyncText);
	Vsyncm->myGameObject = Vsync_Obj;
	Vsyncm->InitAABB();
	Application::GetInstance()->meshRenderer->LoadMesh(Vsyncm);
	Vsynccm->meshes.push_back(Vsyncm);
	Vsync_Obj->AddComponent(Vsynccm);
	Vsync_Obj->UISType = UIState::DISABLED;
	Vsync_Obj->isEnabled = false;

	F1_Create = false;
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
		
		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN )
		{
			if (F1_Screen_Button == false)
			{
				F1_Screen_Button = true;
			}
			else
			{
				F1_Screen_Button = false;
				F1_Screen->isEnabled = false;
				Vsync_Obj->isEnabled = false;
			}

			if (F1_Screen_Button == true)
			{
				if (F1_Screen->isEnabled == false && Vsync_Obj->isEnabled == false) 
				{
					F1_Screen->isEnabled = true;
					Vsync_Obj->isEnabled = true;
				}
			}
		}
		
		//angle += 50 * App->DTG();

		//cameraController->transform->setPosition(float3(cos(angle * DEGTORAD) * -80, 20, sin(angle * DEGTORAD) * -80));
		//cameraController->transform->setRotation(float3(-30, angle - 90, 0));

		//if (angle > 360.0f) angle -= 360.0f;
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
