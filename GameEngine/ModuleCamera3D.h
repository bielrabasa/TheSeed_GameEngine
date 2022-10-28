#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
//#include "MathGeoLib.h"

enum CamStates {
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

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	CamStates camState = NORMAL;

	vec3 X, Y, Z, Position, Reference;

private:
	//DELETE THIS
	vec3 SelectedObject = vec3(0, 3, 0);

	mat4x4 ViewMatrix, ViewMatrixInverse;
};