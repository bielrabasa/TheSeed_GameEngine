#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"
//#include "MathGeoLib.h"

class Transform;

enum class CamStates {
	NORMAL,	//Nothing clicked, default camera movement
	FLYING,	//WASD and mouse "fps like" movement
	FOCUSED,//ALT clicked, mouse movement and rotation
};

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3 &Movement);
	float* GetViewMatrix();

	float3 SelectedObjectPos();

private:

	void CalculateViewMatrix();

public:
	CamStates camState = CamStates::NORMAL;

	Transform t;
};