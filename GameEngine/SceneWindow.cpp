#include "SceneWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ModuleMesh.h"
#include "Transform.h"

ImVec2 SceneWindows::sizeWindScn = {0,0};

void SceneWindows::PrintScene(Application* app)
{
	//Begin scene & get size
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Scene");
	sizeWindScn = ImGui::GetContentRegionAvail();
	
	//Modify by aspect Ratio
	float aspectRatio = sizeWindScn.x / sizeWindScn.y;
	app->camera->cam->SetAspectRatio(aspectRatio);
	ImGui::Image((ImTextureID)app->camera->cam->cameraBuffer, sizeWindScn, ImVec2(0, 1), ImVec2(1, 0));

	//MOUSE PICKING
	if (ImGui::IsMouseClicked(0) && app->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && ImGui::IsWindowHovered())
	{
		std::vector<GameObject*> PickedGO;

		ImVec2 mousePos = ImGui::GetMousePos();
		
		ImVec2 norm = NormMousePos(	ImGui::GetWindowPos().x, 
									ImGui::GetWindowPos().y + ImGui::GetFrameHeight(),
									ImGui::GetWindowSize().x,
									ImGui::GetWindowSize().y - ImGui::GetFrameHeight(), mousePos);

		//TUDU: pla no detecta be depenent del punt de vista
		LineSegment picking = app->camera->cam->frustum.UnProjectLineSegment(norm.x, norm.y);
		app->renderer3D->ls = picking;

		for (size_t i = 0; i < app->meshRenderer->meshes.size(); i++)
		{
			if (picking.Intersects(app->meshRenderer->meshes[i]->OBB_box) && app->meshRenderer->meshes[i]->myGameObject->isEnabled)
			{
				LOG("%d", app->meshRenderer->meshes[i]->num_vertices)

				if (app->meshRenderer->meshes[i]->myGameObject != nullptr)
					PickedGO.push_back(app->meshRenderer->meshes[i]->myGameObject);
			}
		}


		float currentDist;
		float minDist = 0;

		for (size_t i = 0; i < PickedGO.size(); i++)
		{
			Mesh* m = PickedGO[i]->GetComponent<ComponentMesh>()->mesh;
			float4x4 mat = PickedGO[i]->transform->getGlobalMatrix().Transposed();

			for (size_t j = 0; j < m->num_indices; j+=3)
			{
				//Get mesh vertex xyz
				float* v1 = &m->vertices[m->indices[j] * VERTEX_ARGUMENTS];
				float* v2 = &m->vertices[m->indices[j+1] * VERTEX_ARGUMENTS];
				float* v3 = &m->vertices[m->indices[j+2] * VERTEX_ARGUMENTS];

				//Transform vertex
				float4 pT1 = mat * float4(*v1, *(v1 +1), *(v1 +2), 1);
				float4 pT2 = mat * float4(*v2, *(v2 +1), *(v2 +2), 1);
				float4 pT3 = mat * float4(*v3, *(v3 +1), *(v3 +2), 1);

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
		//If no object selected, make nullptr
		if(PickedGO.size() == 0) app->hierarchy->SetGameObjectSelected(nullptr);
		PickedGO.clear();
	}
	ImGui::End();
	ImGui::PopStyleVar();

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