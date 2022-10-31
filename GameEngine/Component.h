#pragma once

class GameObject;

enum class ComponentType {
	TRANSFORM,
	MESH,
	TEXTURE,
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
};