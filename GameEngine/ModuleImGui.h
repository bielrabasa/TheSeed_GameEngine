#ifndef __ModuleImGui_H__
#define __ModuleImGui_H__

#include "Module.h"
#include "SDL/include/SDL.h"

//IMGUI
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

class Application;

class ModuleImGui : public Module
{
public:

	ModuleImGui(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleImGui();
	
	bool Init();

	update_status PreUpdate(float dt);

	update_status Update(float dt);

	update_status PostUpdate(float dt);

	bool CleanUp();


public:
	ImGuiIO io;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

};

#endif // __ModuleImGui_H__