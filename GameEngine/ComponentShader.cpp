#include "ComponentShader.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ModuleMesh.h"
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
	//TUDU: botó per recompilar el shader i lloc on escriure text per el path

	//RecompileShader();
	//path
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
