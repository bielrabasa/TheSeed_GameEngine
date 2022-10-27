#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "GameObject.h"

#include <vector>

class HierarchyWindows : public Module
{
public:

	HierarchyWindows(Application* app, bool start_enabled = true);
	~HierarchyWindows();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void PrintHierarchy();
	void AddGameObj(GameObject* GO);

	std::vector<GameObject*> gameObjects;
};
