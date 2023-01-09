#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

class CameraComponent;

enum class CamStates {
	GOBJECT,	//Nothing clicked, default camera movement
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

	float3 SelectedObjectPos();

private:
	void MouseRotation(float dx, float dy, float sensitivity);

public:
	CameraComponent* cam;
	CamStates camState;
};