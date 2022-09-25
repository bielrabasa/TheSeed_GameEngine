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

	if (ImGui::CollapsingHeader("HEY", false))
	{
		ImGui::Text("counter = %d", counter);
	}
	//ImGui::CollapsingHeader("HEY", false);
	//ImGui::SameLine();

	//
	//ImGuiKey_All = Tab (for now)
	//
	if (ImGui::IsKeyReleased(ImGuiKey_All))
	{
		counter++;
	}
	

	//ImGui::PushID();


	ImGui::Text("Yes bby");
	ImGui::SameLine();
	ImGui::Text("NOPPP");

	ImGui::End();


	ImGui::BeginGroup();


	ImGui::EndGroup();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}