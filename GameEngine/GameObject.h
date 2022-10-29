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

	void AddChild(GameObject* GOP);

	void RemoveChild(GameObject* GO);

private:
	std::vector<Component*> components;

	char aux[255];

	bool isEnable = true;

	bool isSelected = false;
};