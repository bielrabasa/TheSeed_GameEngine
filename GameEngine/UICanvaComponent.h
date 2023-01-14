#pragma once
#include "Component.h"

class UICanvaComponent : public Component
{
public:
	UICanvaComponent();
	~UICanvaComponent();

	void PrintInspector();
	void Update();
	void OnCheck(GameObject* GO);


private:

	bool active = true;
	bool isDragable = false;
};

