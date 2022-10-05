#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "imgui.h"

#include "MathGeoLib.h"

#include "Logs.h"

#include <string>
#include <vector>

struct Mesh;

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



	/*void winPrimitive();*/


private:

	Logs* LogDebug;

	ImVec4* colorEdit2;
	float colorEdit[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

	std::string word = "hola";

	bool IsWireframe = false;
	bool infoWind = false;

	float4 patata;

	Mesh* m;
};