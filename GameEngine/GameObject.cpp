#include "Application.h"
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{
	transform = new Transform();
	components.push_back(transform);

	Application::GetInstance()->hierarchy->gameObjects.push_back(this);
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

void GameObject::AddGameObjectChild(GameObject* GOP)
{
	if (GOP != this)
	{
		this->parent = GOP;
		GOP->childs.push_back(this);
	}
}