#include "Inspector.h"
#include "imgui.h"

string InspectorMenu::name = "Roger";
vector<float> InspectorMenu::trans = {0,0,0,0,0,0,0,0,0};

char InspectorMenu::aux[255];

void InspectorMenu::PrintInspector()
{
	ImGui::Begin("Inspector");
	ImGui::BeginChild("Object_Name");

	//ImGui::Text(name.c_str());
	ImGui::BulletText("Name:");
	ImGui::SameLine();
	//input the name of the Game Object
	ImGui::InputText("##Name", aux, 255);
	name = aux;

	ImGui::Text("");
	ImGui::Separator();
	ImGui::Text("");

	//Transform
	ImGui::BulletText("Tranform");
	//Position values
	ImGui::Text("\tPosition ");  ImGui::SameLine();
	ImGui::InputFloat3("##Pos", &trans[0]);
	//Rotation values
	ImGui::Text("\tRotation ");  ImGui::SameLine();
	ImGui::InputFloat3("##Rot", &trans[3]);
	//Scale values
	ImGui::Text("\tScale\t");  ImGui::SameLine();
	ImGui::InputFloat3("##Scale", &trans[6]);

	ImGui::Text("");
	ImGui::Separator();
	ImGui::Text("");

	ImGui::EndChild();
	ImGui::End();
}