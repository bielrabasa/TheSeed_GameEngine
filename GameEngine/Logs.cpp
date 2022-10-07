#include "Logs.h"
#include "imgui.h"

vector<DebugLogs> Logs::logs;
vector<DebugLogs> Logs::logsCopy;
DebugLogs Logs::logsString = DebugLogs("aa", LogsType::MSGLOG);

bool Logs::isCollapsed = false;

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
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Clear"))
		{
			logs.clear();
			logsCopy.clear();
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

		ImGui::SameLine(ImGui::GetWindowWidth() - 255.f);

		ImGui::Separator();


		ImGui::PushID(3);
		if(warnignDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));
		else if(!warnignDebug)
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 9.3f, 0.65f));

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 9.2f, 4.5f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 9.3f, 3.7f));

		if (ImGui::Button("Warning"))
			warnignDebug = !warnignDebug;

		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::Separator();

		if (ImGui::RadioButton("System", systemDebug))
			systemDebug = !systemDebug;
		
		ImGui::Separator();

		if (ImGui::RadioButton("Logs", msgDebug))
			msgDebug = !msgDebug;

		ImGui::Separator();

		ImGui::EndMenuBar();
	}

	for (size_t i = 0; i < logs.size(); i++)
	{
		if (msgDebug && logs[i].type == LogsType::MSGLOG)
		{
			logsString = logs[i];

			ImGui::Text("%d", logsString.repts);
			ImGui::SameLine();

			ImGui::Text(logsString.st.c_str());
		}
		else if (systemDebug && logs[i].type == LogsType::SYSTEMLOG)
		{
			logsString = logs[i];

			ImGui::Text("%d", logsString.repts);
			ImGui::SameLine();

			ImGui::Text(logsString.st.c_str());
		}
		else if (warnignDebug && logs[i].type == LogsType::WARNINGLOG)
		{
			logsString = logs[i];

			ImGui::Text("%d", logsString.repts);
			ImGui::SameLine();

			ImGui::Text(logsString.st.c_str());
		}
	}

	ImGui::End();
}

void Logs::DebugLog(string format, LogsType type)
{
	if (format.size() <= 0) return;

	if (isCollapsed)
		for (size_t i = 0; i < logs.size(); i++)
		{
			if (logs[i].st == format)
			{
				++logs[i].repts;
				logsCopy.push_back(DebugLogs(format, type));
				return;
			}
		}

	logs.push_back(DebugLogs(format, type));
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
