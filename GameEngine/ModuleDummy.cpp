#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"

#include "Assimp_Logic.h"


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

	return ret;
}

bool ModuleDummy::CleanUp()
{
	LOG("Cleaning test");

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	static int counter = 0;

	ImGui::Begin("HE", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::CollapsingHeader("Button"))
	{
		if (ImGui::Button("Exit"))
		{
			return UPDATE_STOP;
		}
		ImGui::SameLine();
		if (ImGui::ColorButton("ColBut", {1,0,0,1}))
		{
			AddDebug("puta");
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Small"))
		{
			AddDebug("puto ");
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Radio", IsWireframe)) //the true or false its to light up the button
		{
			counter++;
			IsWireframe = !IsWireframe;
		}

		ImGui::Text("counter = %d", counter);
	}

	if (ImGui::CollapsingHeader("Color"))
	{
		ImGui::ColorEdit4("Color Edit", colorEdit);
		//ImGUi::
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

	if (ImGui::IsKeyReleased(ImGuiKey_Tab))
	{
		counter++;
	}
	

	ImGui::End();


	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar);
	ImGui::End();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{

	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
	
	Cube c(1, 1, 1);
	c.Render();


	if(IsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//CAN RENDER
	glBegin(GL_TRIANGLES);

	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(0.f, 1.5f, 0.f);
	glVertex3f(0.f, 0.5f, 1.f);


	glEnd();
	//

	/*
	glBegin(GL_TRIANGLES);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f);
	glEnd();

	glLineWidth(1.0f);*/
	
	PrintDebug();
	return UPDATE_CONTINUE;
}

void ModuleDummy::PrintDebug()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
			//ImGui::ShowStyleSelector("Collapse");

		if (ImGui::RadioButton("Collapse", isCollapsed))
		{
			//ImGui::ColorEdit4("Collapse", colorEdit);
			isCollapsed = !isCollapsed;
		}

	ImGui::EndMenuBar();
	}
	
	for (size_t i = 0; i < logs.size(); i++)
	{
		logsString = logs[i];

		ImGui::Text(logsString.st.c_str());
	}

	ImGui::End();

}

void ModuleDummy::AddDebug(std::string st)
{
	if (st.size() <= 0) return;
	
	if (isCollapsed)
		for (size_t i = 0; i < logs.size(); i++)
		{ 
			if (logs[i].st == st)
			{
				++logs[logs.size() - 1].repts;
				return;
			}
		}

	logs.push_back(DebugLogs(st));
}

