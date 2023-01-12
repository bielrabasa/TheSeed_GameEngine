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

	void UpdateMeshShader();

	void ShaderFromFile(std::string path);
	void RecompileShader();

	std::string path;
	Shader* shader;
};

