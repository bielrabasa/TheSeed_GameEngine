#include "Application.h"
#include "ButtonComponent.h"
#include "Primitives.h"
#include "Transform.h"


UIButtonComponent::UIButtonComponent()
{
	type = ComponentType::UI_BUTTON;

}

UIButtonComponent::~UIButtonComponent()
{
}

void UIButtonComponent::PrintInspector()
{
	if (ImGui::CollapsingHeader("UI Button", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{

		if (ImGui::RadioButton("Active Button", active))
		{
			active = !active;
			if (active)
			{
				LOGT(LogsType::SYSTEMLOG, "Active Button");
			}
			else
			{
				LOGT(LogsType::SYSTEMLOG, "Disable Button");

			}

		}
	}
}

void UIButtonComponent::Update()
{
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr)
	{
		for (size_t i = 0; i < Application::GetInstance()->hierarchy->selectedGameObj->components.size(); ++i)
		{
			if (Application::GetInstance()->hierarchy->selectedGameObj->components[i]->type == ComponentType::UI_BUTTON)
			{
				OnCheck(Application::GetInstance()->hierarchy->selectedGameObj);
			}

		}
	}
}

void UIButtonComponent::OnCheck(GameObject* GO)
{
	if (active != true)
	{
		GO->UISType = UIState::DISABLED;
	}
	else
	{
		switch (GO->UISType)
		{
		case  UIState::ENABLE:

			GO->UISType = UIState::DISABLED;
			break;
		default:
			break;
		}
	}
}


