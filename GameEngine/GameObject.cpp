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

void GameObject::AddChild(GameObject* GOP)
{
	if (GOP != this)
	{
		this->parent = GOP;
		GOP->childs.push_back(this);
	}
}

void GameObject::RemoveChild(GameObject* GO)
{
	if (!GO->childs.empty())
	{
		for (int i = 0; i < childs.size(); ++i) {
			if (childs[i] == GO)
				childs.erase(childs.begin() + 1);
		}
		GO->parent = parent;

		//kill
		GO->parent = nullptr;
		delete GO;
	}

}