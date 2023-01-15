#include "Application.h"
#include "UICanvaComponent.h"
#include "ComponentTexture.h"
#include "Transform.h"
#include "GameWindow.h"


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
		
		if (ImGui::RadioButton("Is Draggable", isDragable))
		{
			isDragable = !isDragable;
			if (isDragable)
			{
				LOGT(LogsType::SYSTEMLOG, "Active Is Draggable");
			}
			else
			{
				LOGT(LogsType::SYSTEMLOG, "Disable Is Draggable");

			}

		}
	}
}

void UICanvaComponent::Update()
{
	if (Application::GetInstance()->hierarchy->selectedGameObj != nullptr)
	{
		for (size_t i = 0; i < Application::GetInstance()->hierarchy->selectedGameObj->components.size(); ++i)
		{
			if (Application::GetInstance()->hierarchy->selectedGameObj->components[i]->type == ComponentType::UI_CANVA)
			{
				OnCheck(Application::GetInstance()->hierarchy->selectedGameObj);
			}

		}
	}
}

void UICanvaComponent::OnCheck(GameObject* GO)
{
	ComponentTexture* ct = new ComponentTexture();
	ImVec2 TamanyWindow;
	GameWindows::vMin;
	GameWindows::vMax;
	TamanyWindow.x = SDL_GetWindowSurface(Application::GetInstance()->window->window)->w; //width total de la pantalla
	TamanyWindow.y = SDL_GetWindowSurface(Application::GetInstance()->window->window)->h; //height total de la pantalla
	ImVec2 NewMousePosOnGame;

	if (Application::GetInstance()->ui->MousePos.x > GameWindows::vMin.x  && Application::GetInstance()->ui->MousePos.x < GameWindows::vMax.x)
	{
		NewMousePosOnGame.x = (Application::GetInstance()->ui->MousePos.x - ((GameWindows::vMin.x + GameWindows::vMax.x)/2))*-1;
		//LOG("X: %f", NewMousePosOnGame.x);
	}

	if (Application::GetInstance()->ui->MousePos.y > GameWindows::vMin.y && Application::GetInstance()->ui->MousePos.y < GameWindows::vMax.y) {
		NewMousePosOnGame.y = (Application::GetInstance()->ui->MousePos.y - ((GameWindows::vMin.y + GameWindows::vMax.y)/2))*-1;
		
	}

		switch (GO->UISType)
		{
		case UIState::PRESSED:
			if (isDragable)
			{
				GO->transform->setPosition(float3{ NewMousePosOnGame.x,NewMousePosOnGame.y,GO->transform->position.z });
			}
			break;
		default:
			break;
		}
}

