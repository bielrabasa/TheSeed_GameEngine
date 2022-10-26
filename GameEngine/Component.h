#pragma once

class Application;

enum class ComponentType {
	TRANSFORM,
	MESH,
	TEXTURE,
};

class Component
{
public:
	Component(bool enabled = true) : enabled(enabled) {}
	virtual ~Component() {}

	
	bool enabled;
	ComponentType type;
	
	virtual void PrintInspector() {}
};