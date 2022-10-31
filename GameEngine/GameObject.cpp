#include "Application.h"
#include "GameObject.h"
#include "HeaderMenu.h"

#include "Component.h"
#include "Transform.h"
#include "ComponentMesh.h"

GameObject::GameObject(bool noParent)
{
	
	transform = new Transform();
	components.push_back(transform);

	parent = nullptr;

	if (noParent) return;

	Application::GetInstance()->hierarchy->rootHierarchy->AddChild(this);
}

GameObject::~GameObject()
{
	//Unbind with parent
	if (parent != nullptr) {
		//Unbind with parent
		parent->RemoveChild(this);
	}

	transform = nullptr;
	
	//Delete Childs
	while (!childs.empty())
	{
		childs.pop_back();
	}

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
	HMenu::ThemeStyleWind();
	HMenu::ThemeStylePopUp();

	ImGui::Begin("Inspector");

	if(parent != nullptr)
	{
		//name i enable
		//ImGui::Text(name.c_str());
		ImGui::BulletText("Name:");
		ImGui::SameLine();

		//input the name of the Game Object
		ImGui::InputText("##Name", aux, 255, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::SameLine();

		ImGui::Checkbox("Enable", &isEnabled);

		if(ImGui::IsKeyDown(ImGuiKey_Enter))
		name = aux;

		for (size_t i = 0; i < components.size(); i++)
		{
			ImGui::Text("");
			ImGui::Separator();
			ImGui::Text("");

			components[i]->PrintInspector();
		}
	}
	ImGui::End();
	ImGui::PopStyleColor(4);

}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

Component* GameObject::GetComponent(ComponentType type)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->type == type) return components[i];
	}
	return nullptr;
}

GameObject* GameObject::getParent()
{
	return parent;
}

bool GameObject::isChildFrom(GameObject* GO)
{
	//if the comparing object is him, return true
	if (GO == this) return true;

	//if GO has no childs (& parent != this), return false
	if (GO->childs.empty()) return false;

	//GO has childs, so they have a potential to be <this>
	for (size_t i = 0; i < GO->childs.size(); i++)
	{
		if (isChildFrom(GO->childs[i])) return true;
	}

	//If no child is <this>, return false
	return false;
}

bool GameObject::AddChild(GameObject* GO)
{
	//If i'm child from GO, can't add child
	if (isChildFrom(GO)) return false;

	//Make child binding
	GO->parent = this;
	childs.push_back(GO);
	return true;
}

bool GameObject::RemoveChild(GameObject* GO)
{
	for (size_t i = 0; i < childs.size(); i++)
	{
		//Find child
		if (childs[i] == GO) {
			GO->parent = nullptr;
			childs.erase(childs.begin() + i);
			return true;
		}
	}
	//No child found
	return false;
}

void GameObject::Free()
{
	//Unbind with parent
	parent->RemoveChild(this);
	//Set hierarchy parent
	parent = Application::GetInstance()->hierarchy->rootHierarchy;
	Application::GetInstance()->hierarchy->rootHierarchy->AddChild(this);
}

bool GameObject::MoveToParent(GameObject* GOparent)
{
	if (parent != nullptr) {
		//return false if the new parent is my child
		if (GOparent->isChildFrom(this)) return false;

		//Unbind from parent
		parent->RemoveChild(this);
	}
	
	//Add me to new parent
	GOparent->AddChild(this);

	return false;
}
