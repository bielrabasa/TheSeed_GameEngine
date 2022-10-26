#pragma once
#include "Globals.h"
#include <string>
#include <vector>

class Component;
class Transform;

class GameObject {
	GameObject();
	~GameObject();
	
public:
	std::string name;
	GameObject* parent;
	Transform* transform;

	void PrintInspector();

private:
	std::vector<Component*> components;
};