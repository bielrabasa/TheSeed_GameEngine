#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"

#include "glew.h"

#include "ImGui_Logic.h"

#define MAX_LIGHTS 8

class CameraComponent;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void RefreshSize();
	void OnResize(int width, int height);
	void InitFrameBuffer();
	
	void DrawBox(float3* corners, float3 color);

private:
	bool refreshSize;

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	float3x3 NormalMatrix;
	float4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	CameraComponent* mainGameCamera;

	unsigned int cameraBuffer;
	unsigned int frameBuffer;
	unsigned int renderObjBuffer;
};