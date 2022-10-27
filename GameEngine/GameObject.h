#pragma once
#include "Globals.h"
#include <string>
#include <vector>

class Component;
class Transform;

class GameObject {
public:
	GameObject();
	~GameObject();
	
	std::string name = "GameObject";
	GameObject* parent = nullptr;
	Transform* transform = nullptr;

	std::vector<GameObject*> childs;

	void PrintInspector();

	void AddGameObjectChild(GameObject* GOP);

	void RemoveGameObjectChild(GameObject* GO);

private:
	std::vector<Component*> components;

	bool isSelected = false;
	bool isActive = true;
};