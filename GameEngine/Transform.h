#pragma once

#include "Component.h"

class Transform : public Component
{
public:
	Transform(bool enabled = true);
	~Transform();

	void PrintInspector();
};