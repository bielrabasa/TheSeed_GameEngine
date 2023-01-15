#pragma once

#include <string>
#include "Component.h"
#include "Shader.h"

class ComponentShader : public Component
{
public:
	ComponentShader(bool enabled = true);
	~ComponentShader();

	void PrintInspector();
	void Update();

	void UpdateMeshShader();

	void ShaderFromFile(std::string path);
	void RecompileShader();

	char pathAux[255] = { "" };
	std::string path;
	Shader* shader;
};

