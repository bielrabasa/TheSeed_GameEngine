#include "HeaderMenu.h"
#include "imgui.h"
#include "SDL.h"

bool HMenu::quit = false;
bool HMenu::openInspector = true;
bool HMenu::openConsole = true;
bool HMenu::openConig = false; 
bool HMenu::openHierarchy = true;
int HMenu::colorStyle = 1;
bool HMenu::styleSelectD = false;
bool HMenu::styleSelectL = true;
bool HMenu::styleSelectSD = false;

void HMenu::PrintMenu()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}

	if(colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if(colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}

	if (ImGui::BeginMainMenuBar())
	{
		
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Git Hub"))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("GitHub", ImVec2(60, 20)))
				ShellExecute(0, 0, "https://github.com/bielrabasa/TheSeed_GameEngine", 0, 0, SW_SHOW);

			if (ImGui::MenuItem("Exit"))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("Exit", ImVec2(60, 20)))
				quit = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Basic Shapes"))
		{
			if (ImGui::Button("Circles", ImVec2(60, 20)))
			{
			}

			if (ImGui::Button("Cube", ImVec2(60, 20)))
			{
			}

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

			ImGui::Separator();

			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem("Light", NULL, &styleSelectL))
				{
					colorStyle = 1;
					styleSelectL = true;
					styleSelectD = false;
					styleSelectSD = false;
				}
				if (ImGui::MenuItem("Soft Dark", NULL, &styleSelectSD))
				{
					colorStyle = 3;
					styleSelectL = false;
					styleSelectD = false;
					styleSelectSD = true;
				}
				if (ImGui::MenuItem("Dark", NULL, &styleSelectD))
				{
					colorStyle = 2;
					styleSelectL = false;
					styleSelectD = true;
					styleSelectSD = false;
				}

				ImGui::EndMenu();
			}

			/*if (ImGui::Checkbox("Config", &openConig))
			{
				openConig = !openConig;
			}*/

			ImGui::EndMenu();
		}
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);

		ImGui::EndMainMenuBar();
	}
}