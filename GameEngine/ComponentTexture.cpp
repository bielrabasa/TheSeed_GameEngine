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
	const char* listTextures[]{ "Loaded", "None", "Chess"};

	//Texture component inspector
	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		ImGui::Text("Texture: ");
		ImGui::SameLine();
		ImGui::Combo("##ChoseTexture", &textureSelected, listTextures, IM_ARRAYSIZE(listTextures));

		/*ImGui::Text("Color base: ");
		ImGui::SameLine();
		ImGui::ColorEdit3("##baseColor", baseColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel );*/
	}

	UpdateMeshTexture();
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
	ComponentMesh* cm = containerParent->GetComponent<ComponentMesh>();
	if (cm == nullptr) return;

	//Send selected texture
	uint text = 0;

	//loaded texture
	if (textureSelected == 0) text = textureId;

	//checkers
	else if (textureSelected == 2) text = Application::GetInstance()->textures->checkersID;

	for (int i = 0; i < cm->meshes.size(); i++) {
		cm->meshes[i]->textureID = text;
	}
}