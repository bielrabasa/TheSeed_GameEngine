#include "Transform.h"
#include "imgui.h"
#include "Globals.h"
#include "GameObject.h"

Transform::Transform(bool enabled) : Component(enabled) {
	type = ComponentType::TRANSFORM;

	//Put everything to 0
	resetMatrix();
}

Transform::~Transform()
{
}

void Transform::PrintInspector()
{
	//Transform
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		//Position values
		ImGui::Text("\tPosition ");  ImGui::SameLine();
		ImGui::InputFloat3("##Pos", position.ptr());
		//Rotation values
		ImGui::Text("\tRotation ");  ImGui::SameLine();
		ImGui::InputFloat3("##Rot", rotation.ptr());
		//Scale values
		ImGui::Text("\tScale\t");  ImGui::SameLine();
		ImGui::InputFloat3("##Scale", scale.ptr());
	}

	calculateMatrix();
}

float4x4 Transform::getGlobalMatrix()
{
	if (containerParent->getParent() == nullptr) return getLocalMatrix();
	
	return  matrix * containerParent->getParent()->transform->getGlobalMatrix();
}

float4x4 Transform::getLocalMatrix()
{
	return matrix;
}

void Transform::resetMatrix()
{
	matrix = float4x4::identity;

	position = float3::zero;
	rotation = float3::zero;
	scale = float3::one;
}

float3 Transform::getPosition(bool globalPosition)
{
	if (!globalPosition)return float3(position);

	float4x4 m = getGlobalMatrix();
	return m.Row3(3);
}

void Transform::setPosition(float3 pos)
{
	position = pos;
	calculateMatrix();
}

float3 Transform::getRotation()
{
	return rotation;
}

void Transform::setRotation(float3 rot)
{
	rotation = rot;
	calculateMatrix();
}

float3 Transform::getScale()
{
	return scale;
}

void Transform::setScale(float3 sca)
{
	scale = sca;
	calculateMatrix();
}

void Transform::FlipChildrenYZRotation()
{
	setRotation(float3(rotation.x, rotation.z, rotation.y));

	for (int i = 0; i < containerParent->childs.size(); i++) {
		containerParent->childs[i]->transform->FlipChildrenYZRotation();
	}
}

void Transform::calculateMatrix()
{
	
	float rx = rotation.x * DEGTORAD;
	float ry = rotation.y * DEGTORAD;
	float rz = rotation.z * DEGTORAD;

	Quat q;
	q = Quat::FromEulerXYZ(rx, ry, rz);
	matrix = float4x4::FromTRS(position, q, scale).Transposed();

	/*
	//Rotation
	matrix[0][0] = cos(rz) * cos(ry) * scale.x;
	matrix[1][0] = -sin(rz) * cos(rx) + cos(rz) * sin(ry) * sin(rx);
	matrix[2][0] = sin(rz) * sin(rx) + cos(rz) * sin(ry) * cos(rx);

	matrix[0][1] = sin(rz) * cos(ry);
	matrix[1][1] = (cos(rz) * cos(rx) + sin(rz) * sin(ry) * sin(rx)) * scale.y;
	matrix[2][1] = -cos(rz) * sin(rx) + sin(rz) * sin(ry) * cos(rx);

	matrix[0][2] = -sin(ry);
	matrix[1][2] = cos(ry) * sin(rx);
	matrix[2][2] = cos(ry) * cos(rx) * scale.z;

	//position
	matrix[3][0] =  position.x;
	matrix[3][1] = position.y;
	matrix[3][2] = position.z;
	
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][3] = 1;*/
}
