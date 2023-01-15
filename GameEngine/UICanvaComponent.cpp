#include "Application.h"
#include "UICanvaComponent.h"
#include "Primitives.h"
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
	if (ImGui::CollapsingHeader("UI InputBox", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{

	
	}
}

void UICanvaComponent::Update()
{
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr)
	{
		for (size_t i = 0; i < Application::GetInstance()->hierarchy->selectedGameObj->components.size(); ++i)
		{
			if (Application::GetInstance()->hierarchy->selectedGameObj->components[i]->type == ComponentType::UI_FONS)
			{
				OnCheck(Application::GetInstance()->hierarchy->selectedGameObj);
			}

		}
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

			GO->UISType = UIState::DISABLED;
			break;
		default:
			break;
		}
	}
}


