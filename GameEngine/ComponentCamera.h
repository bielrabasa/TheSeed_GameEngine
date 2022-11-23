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

	Frustum frustum;
	float3 reference;

	int typeCameraSelected = 0;

	int cameraFOV = 60;
	int farDistance = 500;

	bool isMainCamera = false;

private:
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
};