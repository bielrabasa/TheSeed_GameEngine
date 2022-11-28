#include "GameWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"

ImVec2 GameWindows::sizeWindScn = { 0,0 };

void GameWindows::PrintCamera(Application* app)
{
	//Begin scene & get size
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Game", 0, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNavFocus);
	sizeWindScn = ImGui::GetContentRegionAvail();

	//Get proportion, and match with 16:9
	ImVec2 newWinSize = sizeWindScn;
	newWinSize.x = (newWinSize.y / 9.0f) * 16.0f;

	//Get uv's offset proportionate to image
	float uvOffset = (sizeWindScn.x - newWinSize.x) / 2.0f;
	uvOffset /= newWinSize.x;

	//Print image (window size), modify UV's to match 
	if(app->renderer3D->GetMainCamera() != nullptr)
		ImGui::Image((ImTextureID)app->renderer3D->GetMainCamera()->cameraBuffer, sizeWindScn, ImVec2(-uvOffset, 1), ImVec2(1 + uvOffset, 0));

	ImGui::End();
	ImGui::PopStyleVar();
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}