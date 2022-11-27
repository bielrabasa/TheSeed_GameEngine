#pragma once
#include "Component.h"
#include "MathGeoLib.h"

struct Mesh;

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	void PrintInspector();
	void Update();

	void CreateFrameBuffer();

	void Look(const float3& Position, const float3& Reference);
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);
	void SetAspectRatio(float aspectRatio = 1.7);
	
	float* GetViewMatrix();
	float* GetProjetionMatrix();

	bool IsInsideFrustum(Mesh* mesh);

	Frustum frustum;
	float3 reference;

	int typeCameraSelected = 0;

	int cameraFOV = 60;
	float farDistance = 500.0f;
	float nearDistance = 0.1f;

	bool isMainCamera = false;

	unsigned int cameraBuffer;
	unsigned int frameBuffer;

private:
	float4x4 viewMatrix;
	float4x4 projectionMatrix;

	unsigned int renderObjBuffer;
};