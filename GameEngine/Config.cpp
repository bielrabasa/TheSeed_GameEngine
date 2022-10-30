#include "Config.h"
#include "imgui.h"
#include "HeaderMenu.h"

vector<float> ConfigWindow::fpsDebug;
vector<float> ConfigWindow::fpsDebugAux = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
vector<float> ConfigWindow::timeDebug;
vector<float> ConfigWindow::timeDebugAux = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

bool ConfigWindow::isFullScreen = false;
bool ConfigWindow::isBor = false;
bool ConfigWindow::isRe = true;

bool ConfigWindow::vSync = false;
float ConfigWindow::bright = 0;
bool ConfigWindow::lights = false;
bool ConfigWindow::depths = false;
bool ConfigWindow::isCullFaces = false;
bool ConfigWindow::colorM = false;
bool ConfigWindow::text2D = false;
float ConfigWindow::bright_aux = 0;

void ConfigWindow::PrintConfig(Application* app, float dt)
{
	ImGui::Begin("Configuration", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	if (ImGui::CollapsingHeader("FPS"))
	{
		float fps = 1 / dt;
		float ms = dt * 1000.0f;

		fpsDebug.push_back(fps);
		timeDebug.push_back(ms);


		if(fpsDebug.size() >= 24)
		{
			fpsDebugAux[0] = fpsDebug[fpsDebug.size()-1];
			timeDebugAux[0] = timeDebug[timeDebug.size()-1];
		}

		ImGui::LabelText("The Seed", "Engine Name:");
		ImGui::LabelText("UPC CITM", "Organisation:");

		ImGui::Text("\n");
		ImGui::Text("Min FPS");
		ImGui::SameLine();
		ImGui::SliderInt(" Max FPS", &app->fpsLimit, 9, 200);

		ImGui::Text("\n");
		
		char name[25];
		sprintf_s(name, 25, "FPS %1.f", fpsDebug[fpsDebug.size() - 1]);
		ImGui::PlotHistogram("##_FPS_", &fpsDebug[0], fpsDebugAux.size() , 0, name, 0.0f, 100.0f, ImVec2(400, 75));

		ImGui::Text("\n");

		sprintf_s(name, 25, "Milliseconds %0.f", timeDebug[timeDebug.size() - 1]);
		ImGui::PlotHistogram("##_MS_", &timeDebug[0], timeDebugAux.size(), 0, name, 0.0f, 100.0f, ImVec2(400, 75));

		for (int i = 0; i < fpsDebug.size() - 1; i++)
		{
			fpsDebug[i] = fpsDebug[i + 1];
			timeDebug[i] = timeDebug[i + 1];
		}

		LOGT(LogsType::MSGLOG, "%d", fpsDebug.size());

	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::RadioButton("FullScreen", isFullScreen))
		{
			isFullScreen = !isFullScreen;
			if (isFullScreen)
			{
				GLint m_viewport[4];
				glGetIntegerv(GL_VIEWPORT, m_viewport);
				int HWind =	(int)GetDesktopWindow();
				LOGT(LogsType::SYSTEMLOG, "FullScreen On");
				SDL_SetWindowSize(app->window->window, m_viewport[3], m_viewport[2]);
				SDL_SetWindowFullscreen(app->window->window, SDL_WINDOW_FULLSCREEN); 
			}
			else
			{
				LOGT(LogsType::SYSTEMLOG, "FullScreen Off");
				SDL_SetWindowSize(app->window->window, SCREEN_WIDTH, SCREEN_HEIGHT);
				SDL_SetWindowFullscreen(app->window->window, !SDL_WINDOW_FULLSCREEN);
			}
		}

		if (!isFullScreen) 
		{
			if (ImGui::RadioButton("Resizable", isRe))
			{
				isRe = !isRe;
				if (isRe)
				{
					LOGT(LogsType::SYSTEMLOG, "Resize On");
					SDL_SetWindowResizable(app->window->window, SDL_TRUE); 

				}
				else
				{
					LOGT(LogsType::SYSTEMLOG, "Resize Off");
					SDL_SetWindowResizable(app->window->window, SDL_FALSE); 
				}
			}
			if (ImGui::RadioButton("Borderless", isBor))
			{
				isBor = !isBor;
				if (isBor)
				{
					LOGT(LogsType::SYSTEMLOG, "Border On");
					SDL_SetWindowBordered(app->window->window, SDL_FALSE);
				}
				else
				{
					LOGT(LogsType::SYSTEMLOG, "Border Off");
					SDL_SetWindowBordered(app->window->window, SDL_TRUE); 
				}
			}
		}
		else
		{
			ImGui::BulletText("No Borderless in Full Screen");
			ImGui::BulletText("No Resizable in Full Screen");
		}

		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");
		if(isFullScreen)
		{ 
			ImGui::BulletText("Width: ");
			ImGui::SameLine();
			ImGui::TextColored({ 0,255,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->w);

			ImGui::BulletText("Height: ");
			ImGui::SameLine();
			ImGui::TextColored({ 0,255,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->h);
		}
		else
		{
			ImGui::BulletText("Width: ");
			ImGui::SameLine();
			ImGui::TextColored({ 255,0,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->w);

			ImGui::BulletText("Height: ");
			ImGui::SameLine();
			ImGui::TextColored({ 255,0,0,255 }, "%d", SDL_GetWindowSurface(app->window->window)->h);
		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Visual"))
	{
		if (ImGui::Checkbox("Vsync", &vSync))
		{
			if (vSync)
			{
				SDL_GL_SetSwapInterval(1);
				LOGT(LogsType::SYSTEMLOG, "Vsync On");
			}
			else
			{
				SDL_GL_SetSwapInterval(0);
				LOGT(LogsType::SYSTEMLOG, "Vsync Off");
			}
		}

		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");

		ImGui::BulletText("Brightness");
		ImGui::Text("Min");
		ImGui::SameLine();
		if (ImGui::SliderFloat(" Max", &bright, 0.100f, 1.000f))
		{
			SDL_SetWindowBrightness(app->window->window, bright);
			bright_aux = bright * 100;
			LOGT(LogsType::SYSTEMLOG, "Change Brightness to: %0.0f", bright_aux);
		}

		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");

		if (ImGui::Checkbox("Lights", &lights))
		{
			if (lights)
			{
				glEnable(GL_LIGHTING); 
				LOGT(LogsType::SYSTEMLOG, "Lights On");
			}
			else
			{
				glDisable(GL_LIGHTING);
				LOGT(LogsType::SYSTEMLOG, "Lights Off");
			}
		}

		if (ImGui::Checkbox("Depth Test", &depths))
		{
			if (depths)
			{
				glEnable(GL_DEPTH_TEST);
				LOGT(LogsType::SYSTEMLOG, "Depth On");
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
				LOGT(LogsType::SYSTEMLOG, "Depth Off");
			}
		}

		if (ImGui::Checkbox("Cull Face", &isCullFaces))
		{
			if (isCullFaces)
			{
				glEnable(GL_CULL_FACE); 
				LOGT(LogsType::SYSTEMLOG, "Cull_Face On");
			}
			else
			{
				glDisable(GL_CULL_FACE);
				LOGT(LogsType::SYSTEMLOG, "Cull_Face Off");
			}
		}

		if (ImGui::Checkbox("Color Material", &colorM))
		{
			if (colorM)
			{
				glEnable(GL_COLOR_MATERIAL); 
				LOGT(LogsType::SYSTEMLOG, "Color_Material On");
			}
			else
			{
				glDisable(GL_COLOR_MATERIAL);
				LOGT(LogsType::SYSTEMLOG, "Color_Material Off");
			}
		}

		if (ImGui::Checkbox("Texture 2D", &text2D))
		{
			if (text2D)
			{
				glEnable(GL_TEXTURE_2D);
				LOGT(LogsType::SYSTEMLOG, "Texture_2D On");
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
				LOGT(LogsType::SYSTEMLOG, "Texture_2D Off");
			}
		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");

		SDL_version version;
		SDL_GetVersion(&version);

		ImGui::BulletText("SDL Version:");
		ImGui::SameLine(140);
		ImGui::Text("%u.%u.%u", version.major, version.minor, version.patch);

		ImGui::BulletText("OpenGL Version:");
		ImGui::SameLine(140);
		ImGui::Text("%s", glGetString(GL_VERSION));

		ImGui::BulletText("Glew Version:");
		ImGui::SameLine(140);
		ImGui::Text("%s", glewGetString(GLEW_VERSION));

		ImGui::BulletText("DevIL Version:");
		ImGui::SameLine(140);
		ImGui::Text("%s", glewGetString(GLEW_VERSION)); //ilGetInteger(IL_VERSION_NUM) < IL_VERSION)

		ImGui::Text("\n");
		ImGui::Separator();
		ImGui::Text("\n");

		int SDL_GetCPUCount(void);
		int SDL_GetCPUCacheLineSize(void); 

		ImGui::BulletText("CPUs:");
		ImGui::SameLine(137);
		ImGui::Text("%d", SDL_GetCPUCount());


		int SDL_GetSystemRAM(void);

		ImGui::BulletText("System RAM:");
		ImGui::SameLine(130);
		ImGui::Text("% dGb", SDL_GetSystemRAM() / 1000);

		ImGui::BulletText("Caps:");
		ImGui::SameLine();

		SDL_bool SDL_Has3DNow(void);
		SDL_bool SDL_HasAltiVec(void);
		SDL_bool SDL_HasAVX(void);
		SDL_bool SDL_HasAVX2(void);
		SDL_bool SDL_HasMMX(void);
		SDL_bool SDL_HasRDTSC(void);
		SDL_bool SDL_HasSSE(void);
		SDL_bool SDL_HasSSE2(void);
		SDL_bool SDL_HasSSE3(void);
		SDL_bool SDL_HasSSE41(void);
		SDL_bool SDL_HasSSE42(void);

		if (SDL_Has3DNow())
		{
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("3DNow!");
		}

		if (SDL_HasAltiVec())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("AltiVec");
		}

		if (SDL_HasAVX())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("AVX");
		}

		if (SDL_HasAVX2())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("AVX2");
		}

		if (SDL_HasMMX())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("MMX");
		}

		if (SDL_HasRDTSC())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("RDTSC");
		}

		if (SDL_HasSSE())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE");
		}

		if (SDL_HasSSE2())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE2");
		}

		if (SDL_HasSSE3())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE3");
		}

		if (SDL_HasSSE41())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE41");
		}

		if (SDL_HasSSE42())
		{
			ImGui::Text("\n");
			ImGui::SameLine(130);
			ImGui::BulletText("");
			ImGui::SameLine();
			ImGui::Text("SSE42");
		}
	}

	ImGui::End();
}