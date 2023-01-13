#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "TextEditor.h"

class ShadersEditor : public Module
{
public:

	ShadersEditor(Application* app, bool start_enabled = true);
	~ShadersEditor();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	string inputText;
	char inputTextBuff[255] = {""};

	TextEditor txtEditor;
	TextEditor::LanguageDefinition codeLanguage;

	string txt = "";
};