#pragma once

#include "Component.h"
#include "MathGeoLib.h"
#include <vector>
#include <string>

class Transform : public Component
{
public:
	Transform(bool enabled = true);
	~Transform();

	void PrintInspector();

	//Get transform matrix
	float4x4 getGlobalMatrix();
	float4x4 getLocalMatrix();

	//Put everything to 0
	void resetMatrix();

	//Getters / Setters
	float3 getPosition(bool globalPosition = false);
	void setPosition(float3 pos);
	float3 getRotation();
	void setRotation(float3 rot);
	float3 getScale();
	void setScale(float3 sca);

	void FlipChildrenYZRotation();
	float3 position;
private:
	void calculateMatrix();

	float4x4 matrix;

	float3 rotation;
	float3 scale;
};