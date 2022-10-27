#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "GameObject.h"

#include <vector>
#include <map>

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

	void PrintHierarchy(GameObject* GO);

	void AddGameObj(GameObject* GO);
	void StartGameObject(GameObject* gO, int iterations);
	void SetGameObjectSelected(GameObject* gO);

	std::vector<GameObject*> gameObjects;

	GameObject* rootHierarchy = nullptr;
	GameObject* gameObjectSelected = nullptr;

private:
	GameObject* gameObjectDragging = nullptr;
	GameObject* gameObjectRightClick = nullptr;

	map<uint, GameObject*>* GameObjectCopy;
};
