#include "SceneWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"

ImVec2 SceneWindows::sizeWindScn = {0,0};

void SceneWindows::PrintScene(Application* app)
{
	//Begin scene & get size
	ImGui::Begin("Scene");
	sizeWindScn = ImGui::GetContentRegionAvail();

	//Get proportion, and match with 16:9
	ImVec2 newWinSize = sizeWindScn;
	newWinSize.x = (newWinSize.y / 9.0f) * 16.0f;
	
	//Get uv's offset proportionate to image
	float uvOffset = (sizeWindScn.x - newWinSize.x) / 2.0f;
	uvOffset /= newWinSize.x;

	//Print image (window size), modify UV's to match 
	ImGui::Image((ImTextureID)app->renderer3D->cameraBuffer, sizeWindScn, ImVec2(-uvOffset, 1), ImVec2(1 + uvOffset, 0));

	if (!app->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN && ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
	{
		ImVec2 mousePos = ImGui::GetMousePos();

		ImVec2 norm = NormMousePos(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
					ImGui::GetWindowWidth(), ImGui::GetWindowHeight(), mousePos);

		LOG("%f, %f", norm.x, norm.y);

		LineSegment picking = app->camera->cam->frustum.UnProjectLineSegment(norm.x, norm.y);
		
		/*if (picking.Intersects())
		{
			app->hierarchy->SetGameObjectSelected();
		}*/
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImVec2 SceneWindows::NormMousePos(float x, float y, float w, float h, ImVec2 p)
{
	ImVec2 normP;

	normP.x = ((p.x - x) / w);
	normP.y = ((p.y - y) / h);
	return normP;
}