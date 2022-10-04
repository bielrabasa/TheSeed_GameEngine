#include "Logs.h"
#include "imgui.h"

//bool Logs::isCollapsed = false;

void Logs::PrintDebug()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::RadioButton("Collapse", isCollapsed))
		{
			if (!isCollapsed)
				CollapseDebug();
			else
				UnCollapseDebug();

			isCollapsed = !isCollapsed;
		}

		ImGui::EndMenuBar();
	}

	for (size_t i = 0; i < logs.size(); i++)
	{
		logsString = logs[i];

		ImGui::Text("%d", logsString.repts);
		ImGui::SameLine();


		ImGui::Text(logsString.st.c_str());
	}

	ImGui::End();

}

void Logs::DebugLog(string format)
{
	if (format.size() <= 0) return;

	if (isCollapsed)
		for (size_t i = 0; i < logs.size(); i++)
		{
			if (logs[i].st == format)
			{
				++logs[i].repts;
				logsCopy.push_back(DebugLogs(format));
				return;
			}
		}

	logs.push_back(DebugLogs(format));
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
