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

		strcpy(pathAux, path.c_str());

		if (ImGui::InputTextMultiline("##Shaders Path", pathAux, sizeof(pathAux), ImVec2(ImGui::GetWindowWidth() - 17, 20), inputTextFlags))
		{
			path = pathAux;
			RecompileShader();
		}

		ImGui::Text("");

		if (ImGui::Button("Recompile Shader"))
		{
			RecompileShader();
		}

		ImGui::TextWrapped(shader->compileErrorMessage.c_str());
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
