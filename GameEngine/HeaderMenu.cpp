#include "HeaderMenu.h"
#include "imgui.h"
#include "SDL.h"

bool HMenu::quit = false;
bool HMenu::openInspector = true;
bool HMenu::openConsole = true;
bool HMenu::openConig = false; 
bool HMenu::openHierarchy = true;

void HMenu::PrintMenu()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.14f, 0.14f, 0.14f, 1.0f));
	
	ImGui::Begin("Menus", false, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::Button("GitHub", ImVec2(60,20)))
				ShellExecute(0,0,"https://github.com/bielrabasa/TheSeed_GameEngine", 0,0, SW_SHOW );

			if (ImGui::Button("Exit", ImVec2(60, 20)))
				quit = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Basic Shapes"))
		{
			if (ImGui::Button("Circles", ImVec2(60, 20)))
			{ }
			
			if (ImGui::Button("Cube", ImVec2(60, 20)))
			{ }

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::RadioButton("Inspector", openInspector))
			{
				openInspector = !openInspector;
			}

			if (ImGui::RadioButton("Hierarchy", openHierarchy))
			{
				openHierarchy = !openHierarchy;
			}

			if (ImGui::RadioButton("Console", openConsole))
			{
				openConsole = !openConsole;
			}

			if (ImGui::RadioButton("Config", openConig))
			{
				openConig = !openConig;
			}
			/*if (ImGui::Checkbox("Config", &openConig))
			{
				openConig = !openConig;
			}*/

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::PopStyleColor();
	ImGui::End();
}