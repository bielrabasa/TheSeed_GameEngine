#include "GameWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "SceneWindow.h"
#include "Transform.h"

ImVec2 GameWindows::sizeWindScn = { 0,0 };
ImVec2 GameWindows::vMin = { 0,0 };
ImVec2 GameWindows::vMax = { 0,0 };

void GameWindows::PrintCamera(Application* app)
{
	//Begin scene & get size
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Game", 0, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNavFocus);
	sizeWindScn = ImGui::GetContentRegionAvail();

	//Get GameWindowSize
	{
	vMin = ImGui::GetWindowContentRegionMin();
	vMax = ImGui::GetWindowContentRegionMax();
	
	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;
	}

	//Get proportion, and match with 16:9
	ImVec2 newWinSize = sizeWindScn;
	newWinSize.x = (newWinSize.y / 9.0f) * 16.0f;

	//Get uv's offset proportionate to image
	float uvOffset = (sizeWindScn.x - newWinSize.x) / 2.0f;
	uvOffset /= newWinSize.x;

	//Print image (window size), modify UV's to match 
	if(app->renderer3D->GetMainCamera() != nullptr)
		ImGui::Image((ImTextureID)app->renderer3D->GetMainCamera()->cameraBuffer, sizeWindScn, ImVec2(-uvOffset, 1), ImVec2(1 + uvOffset, 0));
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	int mouse_x, mouse_y;
	Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

	if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT) && app->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && ImGui::IsWindowHovered())
	{
		//Close GO options menu
		app->hierarchy->openGOOptions = false;

		std::vector<GameObject*> PickedGO;

		ImVec2 mousePos = ImGui::GetMousePos();

		ImVec2 norm = SceneWindows::NormMousePos(ImGui::GetWindowPos().x,
			ImGui::GetWindowPos().y + ImGui::GetFrameHeight(),
			ImGui::GetWindowSize().x,
			ImGui::GetWindowSize().y - ImGui::GetFrameHeight(), mousePos);

		LineSegment picking = app->camera->cam->frustum.UnProjectLineSegment(norm.x, norm.y);
		//LineSegment picking = app->renderer3D->mainGameCamera->frustum.UnProjectLineSegment(norm.x, norm.y);

		app->meshRenderer->debugRaycastA = picking.a;
		app->meshRenderer->debugRaycastB = picking.b;

		for (size_t i = 0; i < app->meshRenderer->meshes.size(); i++)
		{
			if (picking.Intersects(app->meshRenderer->meshes[i]->OBB_box) && app->meshRenderer->meshes[i]->myGameObject->isEnabled)
			{
				if (app->meshRenderer->meshes[i]->myGameObject != nullptr)
					PickedGO.push_back(app->meshRenderer->meshes[i]->myGameObject);
				if (app->meshRenderer->meshes[i]->myGameObject->UISType == UIState::DISABLED)
				{
					app->meshRenderer->meshes[i]->myGameObject->UISType = UIState::ENABLE;
				}
			}
		}
		

		float currentDist;
		float minDist = 0;


		for (size_t i = 0; i < PickedGO.size(); i++)
		{
			ComponentMesh* cm = PickedGO[i]->GetComponent<ComponentMesh>();

			for (size_t k = 0; k < cm->meshes.size(); k++)
			{
				Mesh* m = cm->meshes[k];
				float4x4 mat = PickedGO[i]->transform->getGlobalMatrix().Transposed();
				//UI MousePicking Planes
				if (m->num_indices >= 6 && m->myGameObject->type == GameObjectType::UI)
				{
					for (size_t j = 0; j < m->num_indices; j += 3)
					{
						//Get mesh vertex xyz
						float* v1 = &m->vertices[m->indices[j] * VERTEX_ARGUMENTS];
						float* v2 = &m->vertices[m->indices[j + 1] * VERTEX_ARGUMENTS];
						float* v3 = &m->vertices[m->indices[j + 2] * VERTEX_ARGUMENTS];

						//Transform vertex
						float4 pT1 = mat * float4(*v1, *(v1 + 1), *(v1 + 2), 1);
						float4 pT2 = mat * float4(*v2, *(v2 + 1), *(v2 + 2), 1);
						float4 pT3 = mat * float4(*v3, *(v3 + 1), *(v3 + 2), 1);

						//Get vertex position in float3
						float3 _pt1 = float3(pT1.x, pT1.y, pT1.z);
						float3 _pt2 = float3(pT2.x, pT2.y, pT2.z);
						float3 _pt3 = float3(pT3.x, pT3.y, pT3.z);

						//Set triangle
						Triangle triangle(_pt1, _pt2, _pt3);

						//Compare triangle intersecting
						if (picking.Intersects(triangle, &currentDist, nullptr))
						{
							//Set initial minDist
							if (minDist == 0) {
								minDist = currentDist;
								app->hierarchy->SetGameObjectSelected(PickedGO[i]);
								continue;
							}

							//If nearer, select
							if (minDist > currentDist) {
								minDist = currentDist;
								app->hierarchy->SetGameObjectSelected(PickedGO[i]);
							}
						}
					}
				}

			}
		}
		//If no object selected, make nullptr
		if (PickedGO.size() == 0) app->hierarchy->SetGameObjectSelected(nullptr);
		PickedGO.clear();
	}
	ImGui::End();
	ImGui::PopStyleVar();

}
