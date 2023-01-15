#include "Application.h"
#include "InputBoxComponent.h"
#include "Primitives.h"
#include "Transform.h"


InputBoxComponent::InputBoxComponent()
{
	type = ComponentType::UI_INPUTBOX;

}

InputBoxComponent::~InputBoxComponent()
{
}

void InputBoxComponent::PrintInspector()
{
	if (ImGui::CollapsingHeader("UI InputBox", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{

		if (ImGui::RadioButton("Active InputBox", active))
		{
			active = !active;
			if (active)
			{
				LOGT(LogsType::SYSTEMLOG, "Active InputBox");
			}
			else
			{
				LOGT(LogsType::SYSTEMLOG, "Disable InputBox");

			}

		}
	}
}

void InputBoxComponent::Update()
{
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr)
	{
		for (size_t i = 0; i < Application::GetInstance()->hierarchy->selectedGameObj->components.size(); ++i)
		{
			if (Application::GetInstance()->hierarchy->selectedGameObj->components[i]->type == ComponentType::UI_INPUTBOX)
			{
				OnCheck(Application::GetInstance()->hierarchy->selectedGameObj);
			}

		}
	}
}

void InputBoxComponent::OnCheck(GameObject* GO)
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


