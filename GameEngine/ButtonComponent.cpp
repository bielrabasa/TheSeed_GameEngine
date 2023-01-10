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
				LOGT(LogsType::SYSTEMLOG, "Active Button");

			}

		}
	}
}

void UIButtonComponent::Update()
{
	/*if (!active)
	{
		state = State::DISABLED;
	}
	else
	{
		state = State::ENABLE;
	}

	if (state != State::DISABLED)
	{

	}*/
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
			GO->transform->setPosition(float3{0,+1,0});
		default:
			break;
		}
	}
}


