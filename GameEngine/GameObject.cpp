#include "Application.h"
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{
	std::string name = "GameObject";
	parent = nullptr;
	
	transform = new Transform();
	components.push_back(transform);
}

GameObject::~GameObject()
{
	parent = nullptr;
	transform = nullptr;
	
	//Delete Childs
	for (size_t i = 0; i < childs.size(); i++)
	{
		delete childs[i];
		childs[i] = nullptr;
	}
	childs.clear();

	//Delete Components
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
	components.clear();
}

void GameObject::PrintInspector()
{
	//begin()
	//name i enable

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->PrintInspector();
	}

	//end()
}