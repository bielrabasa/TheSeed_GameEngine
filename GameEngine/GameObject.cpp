#include "Application.h"
#include "GameObject.h"
#include "Transform.h"
#include "HeaderMenu.h"

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

	//transform = nullptr;
	
	//Delete Childs
	/*if (!childs.empty())
	{
		for (size_t i = 0; i < childs.size(); i++)
		{
			delete childs[i]; //delet childs done algun que altre problema de excepcio de memoria
			childs[i] = nullptr;
		}
		childs.clear();
	}
	*/

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

		ImGui::Checkbox("Enable", &isEnable);

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

bool GameObject::isChildFrom(GameObject* GO)
{
	//if the comparing object is him, return true
	if (GO == this) return true;

	//if GO has no childs (& parent != this), return false
	if (GO->childs.size() == 0) return false;

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
	if (this->isChildFrom(GO)) return false;

	//Make child binding
	GO->parent = this;
	childs.push_back(GO);
	return true;
}

void GameObject::RemoveChild(GameObject* GO)
{
	for (size_t i = 0; i < childs.size(); i++)
	{
		if (childs[i] == GO) {
			//erase child GO(i) from childs array
		}
	}
}

void GameObject::Free()
{
	//Remove child <this> from parent
	parent = Application::GetInstance()->hierarchy->rootHierarchy;
}