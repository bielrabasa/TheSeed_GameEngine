#include "Logs.h"
#include "imgui.h"

vector<DebugLogs> Logs::logs;
vector<DebugLogs> Logs::logsCopy;

int Logs::countDebug = 0;
int Logs::countSyst = 0;
int Logs::countWarn = 0;

bool Logs::isCollapsed = false;
bool Logs::showPath = false;

bool Logs::warnignDebug = true;
bool Logs::systemDebug = true;
bool Logs::msgDebug = true;

float Logs::colorEdit[3] = { 0.4f, 0.7f, 0.0f };

void Logs::PrintDebug()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		ImGui::Separator();

		
		/*Set the color of the but*/
		ImGui::PushID(1);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.25f, 0.8f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Clear"))
		{
			logs.clear();
			logsCopy.clear();
			countDebug = 0;
			countSyst = 0;
			countWarn = 0;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();


		ImGui::Separator();
		ImGui::Separator();

		if (ImGui::RadioButton("Collapse", isCollapsed))
		{
			if (!isCollapsed)
				CollapseDebug();
			else
				UnCollapseDebug();

			isCollapsed = !isCollapsed;
		}

		ImGui::Separator();

		/*path button*/
		ImGui::SameLine();
		ImGui::Separator();

		if (ImGui::RadioButton("File", showPath))
			showPath = !showPath;

		ImGui::Separator();

		ButtonsTypeLogs();


		ImGui::EndMenuBar();
	}

	for (size_t i = 0; i < logs.size(); i++)
	{
		DebugLogs l = logs[i];
		string s = "";

		if (showPath) {
			s = l.file + l.st;
		}
		else {
			s = l.st;
		}

		if (msgDebug && l.type == LogsType::MSGLOG)
		{
			if (isCollapsed) {
				ImGui::Text("%d |", l.repts);
				ImGui::SameLine();
			}

			ImGui::Text(s.c_str());
		}
		else if (systemDebug && logs[i].type == LogsType::SYSTEMLOG)
		{
			if (isCollapsed) {
				ImGui::Text("%d |", l.repts);
				ImGui::SameLine();
			}

			ImGui::Text(s.c_str());
		}
		else if (warnignDebug && logs[i].type == LogsType::WARNINGLOG)
		{
			if (isCollapsed) {
				ImGui::Text("%d |", l.repts);
				ImGui::SameLine();
			}

			ImGui::Text(s.c_str());
		}
	}

	ImGui::End();
}

void Logs::DebugLog(string format, string file, LogsType type)
{
	if (format.size() <= 0) return;

	if (type == LogsType::MSGLOG)
		countDebug++;

	if (type == LogsType::SYSTEMLOG)
		countSyst++;

	if (type == LogsType::WARNINGLOG)
		countWarn++;


	if (isCollapsed)
		for (size_t i = 0; i < logs.size(); i++)
		{
			if (logs[i].st == format)
			{
				++logs[i].repts;
				logsCopy.push_back(DebugLogs(format, file, type));
				return;
			}
		}

	logs.push_back(DebugLogs(format, file, type));
}

void Logs::CollapseDebug()
{
	//logs copy = before collapse
	logsCopy.clear();
	logsCopy = logs;

	for (int i = 0; i < logs.size(); i++)
	{
		for (int j = i + 1; j < logs.size(); j++)
		{
			if (logs[j].repts > 0)
				if (logs[i].st == logs[j].st)
				{
					logs[i].repts++;
					logs[j].repts = 0;
				}
		}
	}

	//erase all 
	vector<DebugLogs> auxLogs;
	for (int i = 0; i < logs.size(); i++) {
		if (logs[i].repts > 0)
			auxLogs.push_back(logs[i]);
	}
	logs = auxLogs;
	auxLogs.clear();
}

void Logs::UnCollapseDebug()
{
	logs.clear();
	logs = logsCopy;
	logsCopy.clear();
}

void Logs::ButtonsTypeLogs()
{
	// resize buttons type
	if (ImGui::GetWindowWidth() >= 560.0f)
	{
		/*padding last 3 buttons*/
		ImGui::SameLine(ImGui::GetWindowWidth() - 315.0f);

		ImGui::Separator();

		/*Warning button*/
		ImGui::PushID(2);
		if (warnignDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 9.3f, 0.55f));
		else if (!warnignDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 9.0f, 4.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 9.4f, 4.6f));
		ImGui::Text("%d", countWarn); ImGui::SameLine();
		if (ImGui::Button("Warning", ImVec2(60, 20)))
			warnignDebug = !warnignDebug;

		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::Separator();
		ImGui::Separator();

		/*System button*/
		ImGui::PushID(3);
		if (systemDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.165f, 0.80f, 0.8f));
		else if (!systemDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.165f, 9.0f, 4.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.165f, 9.4f, 4.6f));
		ImGui::Text("%d", countSyst); ImGui::SameLine();
		if (ImGui::Button("System", ImVec2(60, 20)))
			systemDebug = !systemDebug;

		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::Separator();
		ImGui::Separator();

		/*Logs button*/
		ImGui::PushID(4);
		if (msgDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.65f, 9.3f, 0.55f));
		else if (!msgDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.65f, 9.0f, 4.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.65f, 9.4f, 4.6f));
		ImGui::Text("%d", countDebug); ImGui::SameLine();
		if (ImGui::Button("Logs", ImVec2(60, 20)))
			msgDebug = !msgDebug;

		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::Separator();
	}
	else
	{
		ImGui::Separator();

		if (ImGui::BeginMenu("Logs Type"))
		{

			/*Warning button*/
			ImGui::PushID(2);
			if (warnignDebug)
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 9.3f, 0.55f));
			else if (!warnignDebug)
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 9.0f, 4.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 9.4f, 4.6f));
			ImGui::Text("%d", countWarn); ImGui::SameLine();
			if (ImGui::Button("Warning", ImVec2(60, 20)))
				warnignDebug = !warnignDebug;

			ImGui::PopStyleColor(3);
			ImGui::PopID();


			/*System button*/
			ImGui::PushID(3);
			if (systemDebug)
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.165f, 0.80f, 0.8f));
			else if (!systemDebug)
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.165f, 9.0f, 4.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.165f, 9.4f, 4.6f));
			ImGui::Text("%d", countSyst); ImGui::SameLine();
			if (ImGui::Button("System", ImVec2(60, 20)))
				systemDebug = !systemDebug;

			ImGui::PopStyleColor(3);
			ImGui::PopID();


			/*Logs button*/
			ImGui::PushID(4);
			if (msgDebug)
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.65f, 9.3f, 0.55f));
			else if (!msgDebug)
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.65f, 9.0f, 4.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.65f, 9.4f, 4.6f));
			ImGui::Text("%d", countDebug); ImGui::SameLine();
			if (ImGui::Button("Logs", ImVec2(60, 20)))
				msgDebug = !msgDebug;

			ImGui::PopStyleColor(3);
			ImGui::PopID();

			ImGui::Separator();

			ImGui::EndMenu();
		}
		ImGui::Separator();

	}
}
