#include "Application.h"
#include "CheckBoxComponent.h"
#include "ComponentTexture.h"
#include "Primitives.h"
#include "Transform.h"


CheckBoxComponent::CheckBoxComponent()
{
	type = ComponentType::UI_CHECKBOX;

}

CheckBoxComponent::~CheckBoxComponent()
{
}

void CheckBoxComponent::PrintInspector()
{
	if (ImGui::CollapsingHeader("CheckBox", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
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

void CheckBoxComponent::Update()
{
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr)
	{
		OnCheck(Application::GetInstance()->hierarchy->selectedGameObj);
	}
}

void CheckBoxComponent::OnCheck(GameObject* GO)
{
	

	switch (GO->UISType)
	{
	case  UIState::PRESSED:
		break;
	case UIState::FOCUSED:

		break;
	case UIState::ENABLE:
		break;
	default:
		break;
	}
}


