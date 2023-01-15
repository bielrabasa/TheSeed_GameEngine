#pragma once
#include "Component.h"

class FonsComponent : public Component
{
public:
	FonsComponent();
	~FonsComponent();

	void PrintInspector();
	void Update();
	void OnCheck(GameObject* GO);


private:

	bool active = true;
	bool isDragable = false;
};

