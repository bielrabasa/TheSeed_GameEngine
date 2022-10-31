#include "Application.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"

ComponentTexture::ComponentTexture(bool enabled)
{
	textureId = 0;
	type = ComponentType::TEXTURE;
}

ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::PrintInspector()
{
}

void ComponentTexture::SetTexture(const char* file_path)
{
	if (textureId != 0) {
		Application::GetInstance()->textures->DestroyTexture(textureId);
		textureId = 0;
	}
	textureId = Application::GetInstance()->textures->LoadTexture(file_path);
	UpdateMeshTexture();
}

void ComponentTexture::ResetTexture()
{
	if (textureId != 0) {
		Application::GetInstance()->textures->DestroyTexture(textureId);
		textureId = 0;
	}
	UpdateMeshTexture();
}

void ComponentTexture::UpdateMeshTexture()
{
	ComponentMesh* cm = containerParent->GetComponentMesh();
	if (cm == nullptr) return;

	cm->mesh->textureID = textureId;
}