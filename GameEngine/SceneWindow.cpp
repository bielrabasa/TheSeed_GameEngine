#include "SceneWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"

ImVec2 SceneWindows::sizeWindScn = {0,0};

void SceneWindows::PrintScene(Application* app)
{

	ImGui::Begin("Scene");

	//with out the size, rescalet okey but crash
	//ImGui::BeginChild("", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));

	//sizeWindScn = ImGui::GetWindowSize();
	sizeWindScn = ImGui::GetContentRegionAvail();

	ImGui::Image((ImTextureID)app->renderer3D->cameraBuffer, sizeWindScn, ImVec2(0, 1), ImVec2(1, 0));

	//ImGui::EndChild();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}