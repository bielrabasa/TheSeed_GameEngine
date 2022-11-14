#include "Transform.h"
#include "imgui.h"
#include "Globals.h"
#include "GameObject.h"

Transform::Transform(bool enabled) : Component(enabled) {
	type = ComponentType::TRANSFORM;
	myGameObject = nullptr;

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
		ImGui::InputFloat3("##Pos", &(position.x, position.y, position.z));
		//Rotation values
		ImGui::Text("\tRotation ");  ImGui::SameLine();
		ImGui::InputFloat3("##Rot", &(rotation.x, rotation.y, rotation.z));
		//Scale values
		ImGui::Text("\tScale\t");  ImGui::SameLine();
		ImGui::InputFloat3("##Scale", &(scale.x, scale.y, scale.z));

		calculateMatrix();
	}
}

float4x4 Transform::getGlobalMatrix()
{
	if (myGameObject->getParent() == nullptr) return getLocalMatrix();
	
	return  myGameObject->getParent()->transform->getGlobalMatrix() * matrix;
}

float4x4 Transform::getLocalMatrix()
{
	return matrix;
}

void Transform::resetMatrix()
{
	matrix = {	1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1 };

	position = { 0, 0, 0 };
	rotation = { 0, 0, 0 };
	scale = { 1, 1, 1 };
}

float3 Transform::getPosition(bool globalPosition)
{
	if (!globalPosition)return float3(position);

	float4x4 m = getGlobalMatrix();
	return m.Col3(4);
	//return float3(m[3], m[7], m[11]);
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

void Transform::calculateMatrix()
{
	/*matrix.SetIdentity();
	matrix.RotateZ(rotation.z * DEGTORAD);
	matrix.RotateY(rotation.y * DEGTORAD);
	matrix.RotateX(rotation.x * DEGTORAD);

	matrix.Translate(position);
	matrix.Scale(scale);*/

	float rx = rotation.x * DEGTORAD;
	float ry = rotation.y * DEGTORAD;
	float rz = rotation.z * DEGTORAD;

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
	matrix[3][3] = 1;
}
