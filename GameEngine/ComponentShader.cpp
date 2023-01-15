#include "Application.h"
#include "ComponentShader.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ModuleMesh.h"
#include "imgui.h"
using namespace std;

ComponentShader::ComponentShader(bool enabled)
{
	shader = new Shader();
	path = "";
}

ComponentShader::~ComponentShader()
{
	delete shader;
}

void ComponentShader::PrintInspector()
{
	if (ImGui::CollapsingHeader("Shader", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::Text("Path:");

		ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CtrlEnterForNewLine;

		//Trim obligatory folders and extension
		string trimmedPath = path;
		trimmedPath = trimmedPath.substr(trimmedPath.find("_Shaders") + 9);
		trimmedPath = trimmedPath.substr(0, trimmedPath.length() - 4);

		strcpy(pathAux, trimmedPath.c_str());

		if (ImGui::InputTextMultiline("##Shaders Path", pathAux, sizeof(pathAux), ImVec2(ImGui::GetWindowWidth() - 17, 20), inputTextFlags))
		{
			//Set full path
			path = "Assets/_Shaders/";
			path.append(pathAux);
			path.append(".txt");

			RecompileShader();
		}

		ImGui::Text("");

		if (ImGui::Button("Recompile Shader"))
		{
			RecompileShader();
		}

		if (shader->uniforms.size() == 0) {
			ImGui::Text("\nNo Uniforms");
		}
		else {
			ImGui::Text("\nUniforms:");
		}

		for (size_t i = 0; i < shader->uniforms.size(); i++) {
			
			switch (shader->uniforms[i].valueType) {
			case UniformType::f1:
			{
				ImGui::InputFloat(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
			}
			break;
			case UniformType::f2:
			{
				ImGui::InputFloat2(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
			}
			break;
			case UniformType::f3:
			{
				ImGui::InputFloat3(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
			}
			break;
			case UniformType::f4:
			{
				ImGui::InputFloat4(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
			}
			break;
			case UniformType::i1:
			{
				ImGui::InputInt(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
			}
			break;
			case UniformType::i2:
			{
				ImGui::InputInt2(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
			}
			break;
			case UniformType::i3:
			{
				ImGui::InputInt3(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
			}
			break;
			case UniformType::i4:
			{
				ImGui::InputInt4(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
			}
			break;
			}
		}

		ImGui::Text("");

		ImGui::TextWrapped(shader->compileErrorMessage.c_str());
	}
}

void ComponentShader::Update()
{
	if (Application::GetInstance()->shadersEdit->pathToRecompile == path) {
		RecompileShader();
	}
}

void ComponentShader::UpdateMeshShader()
{
	if (containerParent == nullptr) return;

	ComponentMesh* cm = containerParent->GetComponent<ComponentMesh>();
	if (cm == nullptr) return;
	
	//Send my shader to meshes shader
	for (size_t i = 0; i < cm->meshes.size(); i++) {
		cm->meshes[i]->shader = shader;
	}
}

void ComponentShader::ShaderFromFile(std::string path)
{
	this->path = path;
	shader->ShaderLoadFromFile(path);
	UpdateMeshShader();
}

void ComponentShader::RecompileShader()
{
	if (shader == nullptr) return;

	shader->ShaderLoadFromFile(path);
}
