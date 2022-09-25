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

	if (ImGui::CollapsingHeader("Button", false))
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

	if (ImGui::CollapsingHeader("Text", false))
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

	if (ImGui::CollapsingHeader("Info", false))
		ImGui::ShowUserGuide();

	//ImGui::CollapsingHeader("HEY", false);

	//
	//ImGuiKey_All = Tab (for now)
	//
	if (ImGui::IsKeyReleased(ImGuiKey_All))
	{
		counter++;
	}
	
	//ImGui::PushID();

	ImGui::End();


	ImGui::BeginGroup();


	ImGui::EndGroup();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}