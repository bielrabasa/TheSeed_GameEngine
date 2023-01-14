#pragma once

class GameObject;

enum class ComponentType {
	TRANSFORM,
	MESH,
	TEXTURE,
	CAMERA,
	UI_BUTTON,
	UI_CANVA,
	UI_CHECKBOX
};

class Component
{
public:
	Component(bool enabled = true) : enabled(enabled), containerParent(nullptr){}
	virtual ~Component() {}

	bool enabled;
	ComponentType type;
	GameObject* containerParent;

	virtual void PrintInspector() {}
	virtual void Update() {}
};