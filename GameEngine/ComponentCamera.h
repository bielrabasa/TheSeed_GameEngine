#pragma once
#include "Component.h"
#include "MathGeoLib.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	void PrintInspector();
	void Update();

	void Look(const float3& Position, const float3& Reference);
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);
	float* GetViewMatrix();
	float* GetProjetionMatrix();

	void SetAspectRatio(float aspectRatio = 1.7);

	Frustum frustum;
	float3 reference;

	int typeCameraSelected = 0;

	int cameraFOV = 60;
	float farDistance = 500.0f;
	float nearDistance = 0.1f;

	bool isMainCamera = false;

private:
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
};