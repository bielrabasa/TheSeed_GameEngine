#include "SceneWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "ModuleMesh.h"

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
	if (ImGui::IsMouseClicked(0, true) && app->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && ImGui::IsWindowHovered())
	{
		std::vector<GameObject*> PickedGO;
		std::vector<GameObject*> TriangleDetectedGO;

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

		for (size_t i = 0; i < PickedGO.size(); i++)
		{
			Mesh* m = PickedGO[i]->GetComponent<ComponentMesh>()->mesh;
			for (size_t j = 0; j < m->num_indices; j+=3)
			{
				float3 pT1, pT2, pT3;
				//TUDU: mirar si coliciona amb un triangle de la mesh
				float* v1 = &m->vertices[m->indices[j] * VERTEX_ARGUMENTS];
				float* v2 = &m->vertices[m->indices[j+1] * VERTEX_ARGUMENTS];
				float* v3 = &m->vertices[m->indices[j+2] * VERTEX_ARGUMENTS];
				pT1 = float3(*v1, *(v1 +1), *(v1 +2));
				pT2 = float3(*v2, *(v2 +1), *(v2 +2));
				pT3 = float3(*v3, *(v3 +1), *(v3 +2));

				Triangle triangle(pT1, pT2, pT3);

				if (picking.Intersects(triangle, nullptr, nullptr))
				{
					//LOG("%f", triangle.a);
					TriangleDetectedGO.push_back(PickedGO[i]);
				}
			}
		}

		if (TriangleDetectedGO.size() != 0)
		{
			app->hierarchy->SetGameObjectSelected(*TriangleDetectedGO.begin());
		}
		PickedGO.clear();
		TriangleDetectedGO.clear();


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