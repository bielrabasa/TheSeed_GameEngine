#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"

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

	ImGui::Begin("HE");

	if (ImGui::CollapsingHeader("Button"))
	{
		//ImGui::Button("Count");
		if (ImGui::Button("Count"))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::ColorButton("ColBut", {1,0,0,1}))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Small"))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Radio", true)) //the true or false its to light up the button
		{
			counter++;
		}

		ImGui::Text("counter = %d", counter);
	}

	if (ImGui::CollapsingHeader("Text"))
	{
		ImGui::Text("Yes bby\n shit happens \"My Love\"");
		ImGui::SameLine();
		ImGui::TextColored({0.9f,0.0f,0.0f,0.9f },"NOPPP");
		ImGui::BulletText("YASSS\n \"The Y\" for the frineds");
		ImGui::Separator();
		ImGui::TextWrapped("YEY");
		ImGui::Separator();
		ImGui::TextUnformatted("YEY");

	}

	if (ImGui::CollapsingHeader("Color"))
	{
		ImGui::ColorEdit4("Color Edit", colorEdit);
		//ImGUi::
		ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f,0.5f);
	}

	if (ImGui::CollapsingHeader("Info"))
		ImGui::ShowUserGuide();


	//
	//ImGuiKey_All = Tab (for now)
	//
	if (ImGui::IsKeyReleased(ImGuiKey_Tab))
	{
		counter++;
	}
	

	ImGui::End();


	ImGui::BeginGroup();


	ImGui::EndGroup();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	Cube c(1, 1, 1);
	c.Render();

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

	return UPDATE_CONTINUE;
}