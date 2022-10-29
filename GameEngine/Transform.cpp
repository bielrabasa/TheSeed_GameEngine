#include "Transform.h"
#include "imgui.h"

Transform::Transform(bool enabled) : Component(enabled) {
	type = ComponentType::TRANSFORM;
}

Transform::~Transform()
{
}

void Transform::PrintInspector()
{
	//Transform
	ImGui::BulletText("Tranform");
	//Position values
	ImGui::Text("\tPosition ");  ImGui::SameLine();
	ImGui::InputFloat3("##Pos", &pos[0]);
	//Rotation values
	ImGui::Text("\tRotation ");  ImGui::SameLine();
	ImGui::InputFloat3("##Rot", &rot[0]);
	//Scale values
	ImGui::Text("\tScale\t");  ImGui::SameLine();
	ImGui::InputFloat3("##Scale", &scale[0]);
}

std::vector<float> Transform::GetPosition()
{
	return pos;
}

std::vector<float> Transform::GetRotation()
{
	return rot;
}

std::vector<float> Transform::GetScale()
{
	return scale;
}