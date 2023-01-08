#pragma once

#include "Component.h"

class UIButtonComponent : public Component
{
public:
	UIButtonComponent();
	~UIButtonComponent();

	void PrintInspector();
	void Update();
	void DrawCheckbox();
private:

	State state;
};

