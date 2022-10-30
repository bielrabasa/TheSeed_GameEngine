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

	//Returns true if <this> is under the GO hierarchy tree
	bool isChildFrom(GameObject* GO);

	//Adds GO child to current gameObject, returns false if <this> is in GO's hierarchy
	bool AddChild(GameObject* GO);

	//Removes GO from childs vector
	void RemoveChild(GameObject* GO);

	//Free <this> from parent, and set it to hierarchy child
	void Free();

private:
	std::vector<Component*> components;

	char aux[255] = {' '};

	bool isEnable = true;

	bool isSelected = false;
};