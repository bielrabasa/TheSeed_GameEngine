#include "Application.h"
#include "UICanvaComponent.h"
#include "Transform.h"


UICanvaComponent::UICanvaComponent()
{
	type = ComponentType::UI_CANVA;

}

UICanvaComponent::~UICanvaComponent()
{
}

void UICanvaComponent::PrintInspector()
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

void UICanvaComponent::Update()
{
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr)
	{
		OnCheck(Application::GetInstance()->hierarchy->selectedGameObj);
	}
}

void UICanvaComponent::OnCheck(GameObject* GO)
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
			GO->transform->setPosition(float3{ 0,12,0 });
		default:
			break;
		}
	}
}


