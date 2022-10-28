#include "Application.h"
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{
	
	transform = new Transform();
	components.push_back(transform);

	parent = nullptr;

	//Application::GetInstance()->hierarchy->rootHierarchy->childs.push_back(this);
	//parent = Application::GetInstance()->hierarchy->rootHierarchy;
}

GameObject::~GameObject()
{
	//Unbind with parent
	/*if (parent != nullptr) {
		parent->RemoveChild(this);
		parent = nullptr;
	}*/

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

void GameObject::AddChild(GameObject* GOP)
{
	if (GOP != this)
	{
		this->parent = GOP;
		GOP->childs.push_back(this);
	}
}

/*void GameObject::RemoveChild(GameObject* GO)
{
	for (int i = 0; i < childs.size(); ++i) {
		if (childs[i] == GO)
			childs.erase(childs.begin() + 1);
	}
	GO->parent = parent;

	//kill
	GO->parent = nullptr;
	delete GO;
}*/