#include "HeaderMenu.h"
#include "imgui.h"
#include "SDL.h"

bool HMenu::quit = false;

void HMenu::PrintMenu()
{
	ImGuiWindowFlags col_Flags = ImGuiCol_WindowBg | ImGuiCol_Border;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	
	ImGui::Begin("Menus", false, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

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
			if (ImGui::Button("Inspector", ImVec2(60, 20)))
			{ }

			if (ImGui::Button("Console", ImVec2(60, 20)))
			{ }

			if (ImGui::Button("Config", ImVec2(60, 20)))
			{ }

			ImGui::EndMenu();
		}
		ImGui::PopStyleColor();
		ImGui::EndMenuBar();
	}
	ImGui::PopStyleColor();
	ImGui::End();
}