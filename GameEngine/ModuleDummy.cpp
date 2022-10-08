#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"
#include "Assimp_Logic.h"
#include "Logs.h"

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

	//MESH TESTING
	/*Mesh m;
	m.num_vertices = 5;
	m.vertices = new float[m.num_vertices * 3];

	m.vertices[0] = 0.0f;	//esq baix
	m.vertices[1] = 1.0f;
	m.vertices[2] = 0.0f;

	m.vertices[3] = 1.0f;	//drt baix
	m.vertices[4] = 1.0f;
	m.vertices[5] = 0.0f;

	m.vertices[6] = 1.0f;	//esq dalt
	m.vertices[7] = 2.0f;
	m.vertices[8] = 0.0f;

	m.vertices[9] = 0.0f;	//drt dalt
	m.vertices[10] = 2.0f;
	m.vertices[11] = 0.0f;

	m.vertices[12] = 0.0f;	//drt lluny
	m.vertices[13] = 1.0f;
	m.vertices[14] = -1.0f;

	m.num_indices = 9;
	m.indices = new uint[m.num_indices];

	m.indices[0] = 0;	//triangle dreta baix
	m.indices[1] = 1;
	m.indices[2] = 2;

	m.indices[3] = 2;	//triangle esquerra dalt
	m.indices[4] = 3;
	m.indices[5] = 0;

	m.indices[6] = 1;	//triangle costat
	m.indices[7] = 4;
	m.indices[8] = 2;

	Assimp_Logic::LoadMesh(&m);*/

	Assimp_Logic::LoadFile("Assets/BakerHouse.fbx");

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

				ImGui::Begin("Settings");
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

	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar);
	ImGui::End();

	return ret;

}

update_status ModuleDummy::PostUpdate(float dt)
{

	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
	
	//Cube c(1, 1, 1);
	//c.Render();


	if(IsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Logs::PrintDebug();

	return UPDATE_CONTINUE;
}