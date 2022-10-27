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
	
	std::string name;
	GameObject* parent;
	Transform* transform;

	void PrintInspector();

private:
	std::vector<GameObject*> childs;
	std::vector<Component*> components;
};