#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#include "MathGeoLib.h"

#include "Logs.h"

#include "GameObject.h"

#include <string>
#include <vector>

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

	void InizializatedUI(GameObject* Canva);
	GameObject* Canva;
	GameObject* Fons;
private:
	GameObject* cameraController;
	bool F1_Screen_Button = false;
	bool F1_Create = true;
	GameObject* F1_Screen = false;
	GameObject* Vsync_Obj = false;


	float angle;
};