#include "Application.h"
#include "ButtonComponent.h"
#include "Primitives.h"

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
		
	}
}

void UIButtonComponent::Update()
{
	DrawCheckbox();
}

void UIButtonComponent::DrawCheckbox()
{
	
}
