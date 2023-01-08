#include "Application.h"
#include "GameObject.h"
#include "HeaderMenu.h"

#include "Component.h"
#include "Transform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentCamera.h"
#include "ButtonComponent.h"
#include "Primitives.h"

GameObject::GameObject(bool noParent)
{
	
	transform = new Transform();
	transform->containerParent = this;
	components.push_back(transform);

	parent = nullptr;

	if (noParent) return;

	Application::GetInstance()->hierarchy->rootHierarchy->AddChild(this);
}

GameObject::GameObject(GameObject* Parent)
{
	transform = new Transform();
	transform->containerParent = this;
	components.push_back(transform);

	parent = nullptr;

	if (Parent != nullptr)
		Parent->AddChild(this);
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
		delete childs[0];
	}
	childs.clear();


	//Delete Components
	for (size_t i = 0; i < components.size(); ++i)
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

	char* listComponents[]{ "Add Component", "Mesh Component", "Texture Component", "Camera Component" , "Button Component"};

	ImGui::Begin("Inspector");

	if(parent != nullptr)
	{
		strcpy(aux, this->name.c_str());
	
		//name i enable
		ImGui::Checkbox("Enable", &isEnabled);

		ImGui::BulletText("Name:");
		ImGui::SameLine();

		//input the name of the Game Object
		ImGui::InputText("##Name", aux, 255, ImGuiInputTextFlags_EnterReturnsTrue);

		if(ImGui::IsKeyDown(ImGuiKey_Enter))
		name = aux;

		for (size_t i = 0; i < components.size(); i++)
		{
			ImGui::Separator();

			components[i]->PrintInspector();
		}

		ImGui::Separator();
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");

		ImGui::Text("");
		ImGui::SameLine(ImGui::GetWindowWidth() / 6);
		if (ImGui::Combo("##AddComponent", &componentNum, listComponents, IM_ARRAYSIZE(listComponents))) //number of total components u can give to a GO
		{
			switch (componentNum) {
			case 1:
			{
				//Mesh component
				if (GetComponent<ComponentMesh>() == nullptr) {
					ComponentMesh* cm = new ComponentMesh();
					AddComponent(cm);
				}
				else {
					LOG("Mesh Component already added, can't duplicate.")
				}
			}
			break;
			case 2:
			{
				if (GetComponent<ComponentTexture>() == nullptr) {
					ComponentTexture* ct = new ComponentTexture();
					AddComponent(ct);
				}
				else {
					LOG("Texture Component already added, can't duplicate.")
				}
			}
			break;
			case 3:
			{
				if (GetComponent<CameraComponent>() == nullptr) {
					CameraComponent* cc = new CameraComponent();
					AddComponent(cc);
				}
				else {
					LOG("Camera Component already added, can't duplicate.")
				}
			}
			break;
			case 4:
			{
				if (GetComponent<UIButtonComponent>() == nullptr) {
					UIButtonComponent* UIB = new UIButtonComponent();
					AddComponent(UIB);
				}
				else {
					LOG("Button Component already added, can't duplicate.")
				}
			}
			break;
			}
			componentNum = 0;
		}
	}
	ImGui::End();
	ImGui::PopStyleColor(4);
}

void GameObject::Update()
{
	for (size_t i = 0; i < childs.size(); i++)
	{
		childs[i]->Update();
	}

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
	component->containerParent = this;
}

template<class T>
T* GameObject::GetComponent()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(T)) return (T*)components[i];
	}

	return nullptr;
}

bool GameObject::isTotalEnabled()
{
	if (parent == nullptr) return isEnabled;

	return parent->isTotalEnabled() ? isEnabled : false;
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

bool GameObject::MenuOptions()
{
	bool isOpen = true;

	ImGui::Begin("Options", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

	if (parent != nullptr)
	{
		ImGui::Separator();
		if (ImGui::MenuItem("Delete"))
		{
			this->killMe = true;
			isOpen = false;
		}
		ImGui::Separator();
		ImGui::Text("");
	}

	ImGui::Text("Add as child:");
	ImGui::Separator();

		if (ImGui::MenuItem("   Empty Object  ")) 
		{
			Primitives::CreatePrimitive(Shapes::EMPTY)->MoveToParent(this);
			isOpen = false;
		}
		ImGui::Separator();
		ImGui::Separator();

		if (ImGui::MenuItem("   Camera  "))
		{
			Primitives::CreatePrimitive(Shapes::CAMERA)->MoveToParent(this);
			isOpen = false;
		}
		ImGui::Separator();
		ImGui::Separator();

		if (ImGui::MenuItem("   Plane "))
		{
			Primitives::CreatePrimitive(Shapes::PLANE)->MoveToParent(this);
			isOpen = false;
		}
		ImGui::Separator();
		ImGui::Separator();

		if (ImGui::MenuItem("   Cube "))
		{
			Primitives::CreatePrimitive(Shapes::CUBE)->MoveToParent(this);
			isOpen = false;
		}
		ImGui::Separator();
		ImGui::Separator();

		if (ImGui::MenuItem("   Sphere "))
		{
			Primitives::CreatePrimitive(Shapes::SPHERE)->MoveToParent(this);
			isOpen = false;
		}
		ImGui::Separator();


	ImGui::End();
	return isOpen;
}
