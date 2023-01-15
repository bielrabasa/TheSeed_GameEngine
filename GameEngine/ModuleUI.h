#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	ImVec2 MousePos;
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void BindUIBuffer();
	void GetComponentype(GameObject* GOSelected);
	void DrawColor();
	int cameraUIFOV = 1000;
	float MoveY = 0;
	bool Move = false;
	bool Vsync = false;
	bool isActive = true;
	std::vector<GameObject*> UIGmo;
	std::vector<GameObject*> PickedUI_OB;

};
