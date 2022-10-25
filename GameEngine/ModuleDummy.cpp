#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Logs.h"
#include "HeaderMenu.h"
#include "Config.h"
#include "Inspector.h"
#include "Hierarchy.h"
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

	return ret;
}

bool ModuleDummy::CleanUp()
{
	LOGT(LogsType::SYSTEMLOG,  "Cleaning test");

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	ImGui::Begin("HE", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::CollapsingHeader("Button"))
	{
		if (ImGui::Button("Exit"))
		{
			ret = UPDATE_STOP;
		}
		ImGui::SameLine();
		if (ImGui::ColorButton("ColBut", {1,0,0,1}))
		{
			//Logs::DebugLog("MAL", "hola");
			LOGT(LogsType::WARNINGLOG, "MAL");
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Small"))
		{
			LOG("BIEN");
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Radio", IsWireframe)) //the true or false its to light up the button
		{
			IsWireframe = !IsWireframe;
		}

		if (ImGui::MenuItem("MenuItem", "Alt + M"))
		{
			LOG("MI");
		}

	}

	if (ImGui::CollapsingHeader("Color"))
	{
		ImGui::ColorEdit4("Color Edit", colorEdit);
		ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f,0.5f);
	}

	if (ImGui::CollapsingHeader("Info Guide"))
		ImGui::ShowUserGuide();

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Text"))
		{ 
			if (ImGui::BeginMenu("SubText"))
			{
					ImGui::Text("Yes bby\n shit happens \"My Love\"");
					ImGui::SameLine();
					ImGui::TextColored({ 0.9f,0.0f,0.0f,0.9f }, "NOPPP");
					ImGui::BulletText("YASSS\n \"The Y\" for the frineds");
					ImGui::Separator();
					ImGui::TextWrapped("YEY");
					ImGui::Separator();
					ImGui::TextUnformatted("YEY");
					ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Info"))
		{
			if (ImGui::Button("Popup"))
			{
				ImGui::OpenPopup("another popup");
			}
			if (ImGui::BeginPopup("another popup"))
			{
				//ImGui::Text("");

				ImGui::Begin("LALA");
				ImGui::Text("Yes bby\n shit happens \"My Love\"");
				ImGui::End();
				ImGui::EndPopup();
			}

			//ImGui::
			/*if (ImGui::Button("Open"))
			{
				ImGui::Begin("Settings");
				ImGui::Text("Yes bby\n shit happens \"My Love\"");
				ImGui::End();
			}*/

			//infoWind = !infoWind;
			ImGui::EndMenu();

		}

		if (infoWind)
		{

		}

		ImGui::BeginPopup;

		ImGui::EndMenuBar();
	}
	ImGui::End();


	//ImGui::DockBuild

	return ret;

}

update_status ModuleDummy::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
	
	//Cube c(1, 1, 1);
	//c.Render();


	



	HMenu::ThemeStyleWind();
	HMenu::ThemeStyleMenuBar();
	HMenu::ThemeStylePopUp();
	
	ImGui::ShowDemoWindow();
	//Print Multiple Windows
	
	if(HMenu::openConsole)
		Logs::PrintDebug();

	if (HMenu::openHierarchy)
		HierarchyWindows::PrintHierarchy();

	if(HMenu::openConig)
		ConfigWindow::PrintConfig(App);

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