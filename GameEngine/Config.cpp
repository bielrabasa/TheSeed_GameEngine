#include "Config.h"
#include "imgui.h"
#include "HeaderMenu.h"

int ConfigWindow::FPSLimit = 60;
vector<float> ConfigWindow::fpsLog;
vector<float> ConfigWindow::timeLog;

bool ConfigWindow::isFullScreen = false;

void ConfigWindow::PrintConfig(Application* app)
{
	ImGui::Begin("Configuration", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	if (ImGui::CollapsingHeader("FPS"))
	{
		ImGui::LabelText("The Seed", "Engine Name:");
		ImGui::LabelText("UPC CITM", "Organisation:");

		ImGui::Text("\n");
		ImGui::Text("Min FPS");
		ImGui::SameLine();
		ImGui::SliderInt("Max FPS", &FPSLimit, 1, 165);

		ImGui::Text("\n");
		ImGui::Text("Limit Framerate: ");

		char title[25];
		sprintf_s(title, 25, "Framerate %1.f", fpsLog[fpsLog.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.f", timeLog[timeLog.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &timeLog[0], timeLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
	}

	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::RadioButton("FullScreen", isFullScreen))
		{
			//LOGT(LogsType::SYSTEMLOG, "%d", isFullScreen);
			isFullScreen = !isFullScreen;
			if (isFullScreen)
			{
				//Active fullscreen
				LOGT(LogsType::SYSTEMLOG, "FullScreen On");
				SDL_SetWindowSize(app->window->window, 1920, 1080);
				SDL_SetWindowFullscreen(app->window->window, SDL_WINDOW_FULLSCREEN); 
			}
			else
			{
				//No active fullscreen
				LOGT(LogsType::SYSTEMLOG, "FullScreen Off");
				SDL_SetWindowSize(app->window->window, SCREEN_WIDTH, SCREEN_HEIGHT);
				SDL_SetWindowFullscreen(app->window->window, !SDL_WINDOW_FULLSCREEN);
			}
		}

		/*if (!fullScreen) //RESIZABLE, BORDER AND SIZE OPTIONS ONLY APPEARS IF IT IS IN WINDOW MODE
		{
			if (ImGui::Checkbox("Resizable", &resizable))
			{
				if (resizable)
				{
					SDL_SetWindowResizable(App->window->window, SDL_TRUE); //RESIZABLE ENABLED
					info.AddConsoleLog(__FILE__, __LINE__, "Resizable Mode Enabled");

				}
				else
				{
					SDL_SetWindowResizable(App->window->window, SDL_FALSE);//RESIZABLE DISABLED
					info.AddConsoleLog(__FILE__, __LINE__, "Resizable Mode Disabled");

				}
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Borderless", &borderless))
			{
				if (borderless)
				{
					SDL_SetWindowBordered(App->window->window, SDL_FALSE); //BORDERLESS ENABLED
					info.AddConsoleLog(__FILE__, __LINE__, "Borderless Mode Enabled");

				}
				else
				{
					SDL_SetWindowBordered(App->window->window, SDL_TRUE); //BORDERLESS DISABLED
					info.AddConsoleLog(__FILE__, __LINE__, "Borderless Mode Disabled");

				}
			}*/


		if(isFullScreen)
		{ 
			ImGui::BulletText("Width: ");
			ImGui::SameLine();
			ImGui::TextColored({ 0,255,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->w);

			ImGui::BulletText("Height: ");
			ImGui::SameLine();
			ImGui::TextColored({ 0,255,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->h);

		}
		else
		{
			ImGui::BulletText("Width: ");
			ImGui::SameLine();
			ImGui::TextColored({ 255,0,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->w);

			ImGui::BulletText("Height: ");
			ImGui::SameLine();
			ImGui::TextColored({ 255,0,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->h);
		}

		}

	ImGui::End();
}