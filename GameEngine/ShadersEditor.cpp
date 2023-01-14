#include "Application.h"
#include "ShadersEditor.h"
#include "HeaderMenu.h"
#include "AssetsWindow.h"

ShadersEditor::ShadersEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ShadersEditor::~ShadersEditor()
{
}

bool ShadersEditor::Init()
{

	return true;
}

bool ShadersEditor::Start()
{
	bool ret = true;

	codeLanguage = TextEditor::LanguageDefinition::GLSL();

	txtEditor.SetLanguageDefinition(codeLanguage);

	return ret;
}

bool ShadersEditor::CleanUp()
{

	return true;
}

update_status ShadersEditor::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status ShadersEditor::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (HMenu::openImputText)
	{
		HMenu::ThemeStyleWind();
		HMenu::ThemeStylePopUp();

		ImGui::Begin("Shaders Editor", 0, ImGuiWindowFlags_NoCollapse);
		

		ImGui::Text("File Name:\t");
		ImGui::SameLine();
		ImGui::Text("WaterShader");

		ImGui::Text("");

		if (ImGui::Button("Save Shader"))
		{
			App->assets->SaveTXT(txt, relDocPath);
		}

		ImGui::SameLine();

		if (ImGui::Button("Create Shader"))
		{
			App->assets->CreateTXT();
		}

		ImGui::SameLine();


		//TUDU: llista de paths
		char* listTXT[]{ "Shader.txt", "New_Folder/Shader.txt", "Texture Component", "Shader Component", "Camera Component" };
		if(ImGui::Combo("##listTXT", &txtNum, listTXT, IM_ARRAYSIZE(listTXT)))
		{
			relDocPath = string(listTXT[txtNum]);
			string text = App->assets->LoadTXT(relDocPath);

			if (text == "SHADER_EDITOR_ERROR") {
				txtEditor.SetReadOnly(true);
			}
			else {
				txtEditor.SetReadOnly(false);
			}
			
			txtEditor.SetText(text);
		}

		ImGui::Text("");

		/*ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_AllowTabInput; // | ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue| ImGuiInputTextFlags_Password

		if (ImGui::InputTextMultiline("##Shaders Texts", inputTextBuff, 255, ImVec2(ImGui::GetWindowWidth() - 17, 0), inputTextFlags))
		{
			inputText = inputTextBuff;
		}

		ImGui::Text(inputText.c_str());*/

		txtEditor.Render("Shader Editor");
		txt = txtEditor.GetText();

		ImGui::End();

		ImGui::PopStyleColor(4);
	}

	return ret;
}

update_status ShadersEditor::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}