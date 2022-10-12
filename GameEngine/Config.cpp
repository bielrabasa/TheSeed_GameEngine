#include "Config.h"
#include "imgui.h"

int ConfigWindow::FPSLimit = 60;
/*vector<float> ConfigWindow::fpsLog = nullptr;
vector<float> ConfigWindow::timeLog = nullptr;
*/
void ConfigWindow::PrintConfig()
{


	ImGui::Begin("Configuration", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::CollapsingHeader("FPS"))
	{
		/*ImGui::LabelText("The Seed", "App Name:");
		ImGui::LabelText("UPC CITM", "Organisation:");
		ImGui::SliderInt("Max FPS", &FPSLimit, 1, 165);

		ImGui::Text("Limit Framerate: ");

		char title[25];
		sprintf_s(title, 25, "Framerate %1.f", fpsLog[fpsLog.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.f", timeLog[timeLog.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &timeLog[0], timeLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));*/

	}

	ImGui::End();
}