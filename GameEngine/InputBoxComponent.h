#pragma once
#include "Component.h"


class InputBoxComponent : public Component
{
public:
	InputBoxComponent();
	~InputBoxComponent();

	void PrintInspector();
	void Update();
	void OnCheck(GameObject* GO);


private:

	bool active = true;

};

