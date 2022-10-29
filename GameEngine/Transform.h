#pragma once

#include "Component.h"
#include "glmath.h"
#include <vector>

class Transform : public Component
{
public:
	Transform(bool enabled = true);
	~Transform();

	void PrintInspector();

	//Get transform matrix
	mat4x4 getMatrix();

	//Put everything to 0
	void resetMatrix();

	//Getters / Setters
	vec3 getPosition();
	void setPosition(vec3 pos);
	vec3 getRotation();
	void setRotation(vec3 rot);
	vec3 getScale();
	void setScale(vec3 sca);

private:
	void calculateMatrix();

	mat4x4 matrix;
	vec3 position;
	vec3 rotation;
	vec3 scale;

};