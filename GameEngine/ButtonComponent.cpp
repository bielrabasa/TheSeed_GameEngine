#include "Application.h"
#include "ButtonComponent.h"
#include "Primitives.h"

UIButtonComponent::UIButtonComponent()
{
}

UIButtonComponent::~UIButtonComponent()
{
}

void UIButtonComponent::PrintInspector()
{
	int hola = 0;
}

void UIButtonComponent::Update()
{
	DrawCheckbox();
}

void UIButtonComponent::DrawCheckbox()
{
	Primitives::CreatePrimitive(Shapes::PLANE);
}
