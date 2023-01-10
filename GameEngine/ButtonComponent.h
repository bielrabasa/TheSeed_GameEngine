#pragma once

#include "Component.h"

class UIButtonComponent : public Component
{
public:
	UIButtonComponent();
	~UIButtonComponent();

	void PrintInspector();
	void Update();
	void OnCheck(GameObject* GO);
private:

	bool active = true;
	//State state;
};

