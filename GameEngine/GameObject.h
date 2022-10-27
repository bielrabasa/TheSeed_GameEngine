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

	int index = 0;
	std::vector<GameObject*> childs;

	void PrintInspector();

private:
	std::vector<Component*> components;
};