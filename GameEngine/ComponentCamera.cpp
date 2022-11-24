#include "ComponentCamera.h"
#include "GameObject.h"
#include "Transform.h"
#include "imgui.h"
#include "Application.h"

CameraComponent::CameraComponent()
{
	//Component
	type = ComponentType::CAMERA;
	containerParent = nullptr;

	//Frustum
	frustum.type = PerspectiveFrustum;
	frustum.nearPlaneDistance = nearDistance;
	frustum.farPlaneDistance = farDistance; //inspector
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = cameraFOV * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...
	frustum.pos = float3(0, 0, 0);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::PrintInspector()
{
	//TUDU en el header menu, en el desplegable de render, camera options alla.

	//Roger tu turno
	const char* listType[]{ "Perspective", "Orthographic" };

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		//is main camera??
		if (isMainCamera)
		{
			ImGui::SameLine();
			ImGui::Text(" ( Main Camera )");
		}

		ImGui::Text("");

		//Chose type of camera
		ImGui::Text("Camera type: ");
		ImGui::SameLine();
		if (ImGui::Combo("##CameraType", &typeCameraSelected, listType, IM_ARRAYSIZE(listType)))
		{
			if(typeCameraSelected == 0)
				frustum.type = PerspectiveFrustum;

			if(typeCameraSelected == 1)
				frustum.type = OrthographicFrustum;

			Application::GetInstance()->renderer3D->RefreshSize();
		}

		ImGui::Text("");

		//Fov camera
		ImGui::Text("FOV\t\t  ");
		ImGui::SameLine();
		if (ImGui::SliderInt("##FOVert", &cameraFOV, 10, 200))
		{
			frustum.verticalFov = cameraFOV * DEGTORAD;
			frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f);
			Application::GetInstance()->renderer3D->RefreshSize();
		}

		ImGui::Text("");

		//Slider Set Near Distane
		ImGui::Text("Near Distance\t");
		ImGui::SameLine();
		if (ImGui::InputFloat("##nearDistance", &nearDistance))
		{
			if (nearDistance >= farDistance)
			{
				farDistance = nearDistance + 1;
				frustum.farPlaneDistance = farDistance;
			}

			frustum.nearPlaneDistance = nearDistance;
			Application::GetInstance()->renderer3D->RefreshSize();
		}

		ImGui::Text("");

		//Slider Set Far Distane
		ImGui::Text("Far Distance\t ");
		ImGui::SameLine();
		if (ImGui::InputFloat("##farDistance", &farDistance))
		{
			if (farDistance <= nearDistance)
			{
				nearDistance = farDistance - 1;
				frustum.nearPlaneDistance = nearDistance;
			}

			frustum.farPlaneDistance = farDistance;
			Application::GetInstance()->renderer3D->RefreshSize();
		}
		
		ImGui::Text("");

		//Button Set main camera
		ImGui::Text("");
		ImGui::SameLine((ImGui::GetWindowWidth() / 2) - 75);
		if (ImGui::Button("Set as main camera", ImVec2(150,25)))
		{
			isMainCamera = true;

			//TUDU Biel, tu turno de les funcioncitas
		}
	}
}

void CameraComponent::Update()
{
	if (containerParent == nullptr) return;

	frustum.pos = containerParent->transform->getPosition();
	float4x4 m = containerParent->transform->getGlobalMatrix();
	frustum.up = m.RotatePart().Col(1).Normalized();
	frustum.front = m.RotatePart().Col(2).Normalized();
}

void CameraComponent::Look(const float3& Position, const float3& Reference)
{
	frustum.pos = Position;
	reference = Reference;

	LookAt(reference);
}

void CameraComponent::LookAt(const float3& Spot)
{
	reference = Spot;
	frustum.front = (Spot - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}

void CameraComponent::Move(const float3& Movement)
{
	frustum.pos += Movement;
}

float* CameraComponent::GetViewMatrix()
{
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	return viewMatrix.ptr();
}

float* CameraComponent::GetProjetionMatrix()
{
	projectionMatrix = frustum.ProjectionMatrix();
	projectionMatrix.Transpose();
	return projectionMatrix.ptr();
}