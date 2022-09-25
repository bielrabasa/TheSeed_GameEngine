#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"

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

	ImGui::CollapsingHeader("HEY", false);
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	if (ImGui::IsKeyReleased(ImGuiKey_All))
	{
		counter++;
	}


	//ImGui::PushID();


	ImGui::Text("Yes bby");
	ImGui::SameLine();
	ImGui::Text("NOPPP");

	ImGui::End();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}