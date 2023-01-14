#pragma once
#include "Component.h"

class CheckBoxComponent : public Component
{
public:
	CheckBoxComponent();
	~CheckBoxComponent();

	void PrintInspector();
	void Update();
	void OnCheck(GameObject* GO);
	uint CBTexture;


private:

	bool active = true;
	bool isDragable = false;
	bool AddTexture = false;
};

