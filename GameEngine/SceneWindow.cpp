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
	
	//Modify by aspect Ratio
	float aspectRatio = sizeWindScn.x / sizeWindScn.y;
	app->camera->cam->SetAspectRatio(aspectRatio);
	ImGui::Image((ImTextureID)app->renderer3D->cameraBuffer, sizeWindScn, ImVec2(0, 1), ImVec2(1, 0));

	//MOUSE PICKING
	if (!app->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN && ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered() && ImGui::IsWindowFocused())
	{
		ImVec2 mousePos = ImGui::GetMousePos();
		
		ImVec2 norm = NormMousePos(	ImGui::GetWindowPos().x, 
									ImGui::GetWindowPos().y, 
									ImGui::GetWindowSize().x,
									ImGui::GetWindowSize().y, mousePos);

		//LOG("%f, %f", norm.x, norm.y);

		//TUDU: mirar xk no detecta la esfera
		//TUDU: pla no detecta be depenent del punt de vista

		LineSegment picking = app->camera->cam->frustum.UnProjectLineSegment(norm.x, norm.y);

		for (size_t i = 0; i < app->meshRenderer->meshes.size() - 1; i++)
		{
			if (picking.Intersects(app->meshRenderer->meshes[i]->OBB_box))
			{
				LOG("%d", app->meshRenderer->meshes[i]->num_vertices)
				//app->hierarchy->SetGameObjectSelected(app->hierarchy->GOscene[i]);
			}
		}

	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImVec2 SceneWindows::NormMousePos(float x, float y, float w, float h, ImVec2 p)
{
	ImVec2 normP;

	normP.x = -1.0 + 2.0 * ((p.x - x) / w);
	normP.y = 1.0 - 2.0 * ((p.y - y) / h);

	return normP;
}