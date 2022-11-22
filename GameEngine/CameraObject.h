#pragma once
#include "GameObject.h"
#include "MathGeoLib.h"

class CameraObject : public GameObject
{
public:
	CameraObject(bool noParent = false);
	~CameraObject();

	void Look(const float3& Position, const float3& Reference);
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);
	float* GetViewMatrix();
	float* GetProjetionMatrix();

	Frustum frustum;
	float3 reference;

private:
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
};

