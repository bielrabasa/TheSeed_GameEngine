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
		
		if (ImGui::Button("Create Shader"))
		{
			App->assets->CreateTXT();
		}

		//TUDU: crec que no pilla mes de 255 caracters, mirar dampliar el buffer o netejar-lo
		ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_AllowTabInput; // | ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue| ImGuiInputTextFlags_Password

		if (ImGui::InputTextMultiline("##Shaders Texts", inputTextBuff, 255, ImVec2(ImGui::GetWindowWidth() - 17, 0), inputTextFlags))
		{
			inputText = inputTextBuff;
		}

		ImGui::Text(inputText.c_str());

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