#include "Transform.h"
#include "imgui.h"
#include "Globals.h"

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
		ImGui::InputFloat3("##Pos", &position);
		//Rotation values
		ImGui::Text("\tRotation ");  ImGui::SameLine();
		ImGui::InputFloat3("##Rot", &rotation);
		//Scale values
		ImGui::Text("\tScale\t");  ImGui::SameLine();
		ImGui::InputFloat3("##Scale", &scale);

		calculateMatrix();


	}
}

mat4x4 Transform::getGlobalMatrix()
{
	return transpose(matrix);
}

mat4x4 Transform::getLocalMatrix()
{
	return transpose(matrix);
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

vec3 Transform::getPosition()
{
	return position;
}

void Transform::setPosition(vec3 pos)
{
	position = pos;
	calculateMatrix();
}

vec3 Transform::getRotation()
{
	return rotation;
}

void Transform::setRotation(vec3 rot)
{
	rotation = rot;
	calculateMatrix();
}

vec3 Transform::getScale()
{
	return scale;
}

void Transform::setScale(vec3 sca)
{
	scale = sca;
	calculateMatrix();
}

void Transform::calculateMatrix()
{
	float rx = rotation.x * DEGTORAD;
	float ry = rotation.y * DEGTORAD;
	float rz = rotation.z * DEGTORAD;

	//Rotation
	matrix[0] = cos(rz) * cos(ry) * scale.x;
	matrix[1] = -sin(rz) * cos(rx) + cos(rz) * sin(ry) * sin(rx);
	matrix[2] = sin(rz) * sin(rx) + cos(rz) * sin(ry) * cos(rx);

	matrix[4] = sin(rz) * cos(ry);
	matrix[5] = (cos(rz) * cos(rx) + sin(rz) * sin(ry) * sin(rx)) * scale.y;
	matrix[6] = -cos(rz) * sin(rx) + sin(rz) * sin(ry) * cos(rx);

	matrix[8] = -sin(ry);
	matrix[9] = cos(ry) * sin(rx);
	matrix[10] = cos(ry) * cos(rx) * scale.z;

	//position
	matrix[3] = position.x;
	matrix[7] = position.y;
	matrix[11] = position.z;
	
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;
}
