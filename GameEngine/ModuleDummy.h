#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "imgui.h"

#include <string>
#include <vector>

struct DebugLogs
{
	DebugLogs() : st("ERROR, missage not found") {};

	DebugLogs(std::string st) : st(st), repts(1) {};

	std::string st;
	int repts;
};

class ModuleDummy : public Module
{
public:

	ModuleDummy(Application* app, bool start_enabled = true);
	~ModuleDummy();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void PrintDebug();
	void AddDebug(std::string st);


private:

	ImVec4* colorEdit2;
	float colorEdit[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

	std::string word = "hola";

	std::vector<DebugLogs> logs;
	DebugLogs logsString;

	bool isCollapsed = false;
	bool IsWireframe = false;
	bool infoWind = false;
};