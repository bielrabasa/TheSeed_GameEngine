#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"

#include "glew.h"

#include "ImGui_Logic.h"

#define MAX_LIGHTS 8

class CameraComponent;
class Shader;

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

	void DrawBox(float3* corners, float3 color);
	void DrawLine(float3 a, float3 b, float3 color);

	void SetMainCamera(CameraComponent* cam);
	CameraComponent* GetMainCamera();

private:
	void BindCameraBuffer(CameraComponent* cc);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	float3x3 NormalMatrix;
	float4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	Shader* textureShader;
	Shader* defaultShader;
private:
	CameraComponent* mainGameCamera;
};