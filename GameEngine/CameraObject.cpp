#include "CameraObject.h"

CameraObject::CameraObject(bool noParent) : GameObject(noParent)
{
	frustum.type = PerspectiveFrustum;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 500.f;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...
	frustum.pos = float3(0, 0, 0);
}

CameraObject::~CameraObject()
{
}

void CameraObject::Look(const float3& Position, const float3& Reference)
{
	frustum.pos = Position;
	reference = Reference;

	LookAt(reference);
}

void CameraObject::LookAt(const float3& Spot)
{
	reference = Spot;
	frustum.front = (Spot - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}

void CameraObject::Move(const float3& Movement)
{
	frustum.pos += Movement;
}

float* CameraObject::GetViewMatrix()
{
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	return viewMatrix.ptr();
}

float* CameraObject::GetProjetionMatrix()
{
	projectionMatrix = frustum.ProjectionMatrix();
	projectionMatrix.Transpose();
	return projectionMatrix.ptr();
}