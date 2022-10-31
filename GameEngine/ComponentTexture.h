#pragma once

#include "Component.h"
#include "Globals.h"

struct Mesh;

class ComponentTexture : public Component
{
public:
	ComponentTexture(bool enabled = true);
	~ComponentTexture();

	void PrintInspector();

	//Set file_path texture
	void SetTexture(const char* file_path);

	//Set default texture
	void ResetTexture();
	uint textureId;

private:
	void UpdateMeshTexture();
};