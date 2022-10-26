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