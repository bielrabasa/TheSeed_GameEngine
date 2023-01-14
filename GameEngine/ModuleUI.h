#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void BindUIBuffer();
	void GetComponentype(GameObject* GOSelected);
	void DrawColor();
	std::vector<GameObject*> UIGmo;
	std::vector<GameObject*> PickedUI_OB;
};
