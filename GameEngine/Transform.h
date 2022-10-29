#pragma once

#include "Component.h"

#include <vector>

class Transform : public Component
{
public:
	Transform(bool enabled = true);
	~Transform();

	void PrintInspector();
	std::vector<float> GetPosition();
	std::vector<float> GetRotation();
	std::vector<float> GetScale();

	std::vector<float> pos = { 0,0,0 };
	std::vector<float> rot = { 0,0,0 };
	std::vector<float> scale = { 0,0,0 };
};