#pragma once
#include "Application.h"

#include "SDL_opengl.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

class ImGui_Logic {

public:
	static Application* App;

	static ImGuiIO* io;

	static void Init();

	static void NewFrame();

	static void Render();

	static void CleanUp();
};