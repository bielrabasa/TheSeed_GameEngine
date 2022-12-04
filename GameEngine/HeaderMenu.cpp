#include "HeaderMenu.h"
#include "imgui.h"
#include "SDL.h"
#include "Primitives.h"
#include "Application.h"
#include "ComponentCamera.h"

bool HMenu::quit = false;
bool HMenu::openInspector = true;
bool HMenu::openConsole = true;
bool HMenu::openConig = true; 
bool HMenu::openHierarchy = true;
bool HMenu::openAssets = true;
bool HMenu::styleSelectD = false;
bool HMenu::styleSelectL = false;
bool HMenu::styleSelectSD = true;
bool HMenu::styleSelectP = false;
bool HMenu::isWireframe = false;
bool HMenu::isBoundingBoxes = false;

bool HMenu::popUpAbout = false;

int HMenu::colorStyle = 4;

uint HMenu::playTexture = 0;
uint HMenu::stopTexture = 0;
uint HMenu::pausedTexture = 0;
uint HMenu::NOpausedTexture = 0;
uint HMenu::speedx1 = 0;
uint HMenu::speedx2 = 0;
uint HMenu::speedx3 = 0;

uint HMenu::pauseButton= 0;
uint HMenu::playButton= 0;
uint HMenu::speedButton= 0;

//float HMenu::colorWind[4] = { 0.4f, 0.7f, 0.0f, 1.0f };
//float HMenu::colorText[4] = { 0.9f, 0.0f, 1.0f, 1.0f };
float HMenu::colorWind[4] = { 0.1176f, 0.1176f, 0.1176f, 1.0f };
float HMenu::colorText[4] = { 0.0f, 0.902f, 1.0f, 1.0f };

void HMenu::PrintMenu(Application* app)
{
	ThemeStylePopUp();
	ThemeStyleMenuBar();

	if (ImGui::BeginMainMenuBar())
	{	
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("  About  "))
			{
				popUpAbout = !popUpAbout;
			}

			if (ImGui::MenuItem("  Git Hub  "))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("GitHub", ImVec2(60, 20)))
				ShellExecute(0, 0, "https://github.com/bielrabasa/TheSeed_GameEngine", 0, 0, SW_SHOW);

			if (ImGui::MenuItem("  Exit  "))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("Exit", ImVec2(60, 20)))
				quit = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Basic Shapes"))
		{
			if (ImGui::MenuItem(" Empty Object  ")) {
				Primitives::CreatePrimitive(Shapes::EMPTY);
			}

			if (ImGui::MenuItem(" Camera "))
			{
				Primitives::CreatePrimitive(Shapes::CAMERA);
			}

			if (ImGui::MenuItem(" Plane  "))
			{
				Primitives::CreatePrimitive(Shapes::PLANE);
			}

			if (ImGui::MenuItem(" Cube  "))
			{
				Primitives::CreatePrimitive(Shapes::CUBE);
			}

			if (ImGui::MenuItem(" Sphere  "))
			{
				Primitives::CreatePrimitive(Shapes::SPHERE);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			
			if (ImGui::RadioButton(" Inspector  ", openInspector))
			{
				openInspector = !openInspector;
			}

			if (ImGui::RadioButton(" Hierarchy  ", openHierarchy))
			{
				openHierarchy = !openHierarchy;
			}

			if (ImGui::RadioButton(" Console  ", openConsole))
			{
				openConsole = !openConsole;
			}

			if (ImGui::RadioButton(" Config  ", openConig))
			{
				openConig = !openConig;
			}
			
			if (ImGui::RadioButton(" Assets  ", openAssets))
			{
				openAssets = !openAssets;
			}

			ImGui::Separator();

			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem(" Light  ", NULL, &styleSelectL))
				{
					colorStyle = 1;
					styleSelectL = true;
					styleSelectD = false;
					styleSelectSD = false;
					styleSelectP = false;
				}
				if (ImGui::MenuItem(" Soft Dark  ", NULL, &styleSelectSD))
				{
					colorStyle = 3;
					styleSelectL = false;
					styleSelectD = false;
					styleSelectSD = true;
					styleSelectP = false;
				}
				if (ImGui::MenuItem(" Dark  ", NULL, &styleSelectD))
				{
					colorStyle = 2;
					styleSelectL = false;
					styleSelectD = true;
					styleSelectSD = false;
					styleSelectP = false;
				}

				if (ImGui::BeginMenu(" Personalised "))
				{
					ImGui::ColorEdit4("Windows Color", colorWind);
					ImGui::ColorEdit4("Text Color", colorText);

					if (ImGui::MenuItem(" Apply  ", NULL, &styleSelectP))
					{
						colorStyle = 4;
						styleSelectL = false;
						styleSelectD = false;
						styleSelectSD = false;
						styleSelectP = true;
					}
					ImGui::Text("");

					ImGui::EndMenu();
				}
				ImGui::Text("");

				ImGui::EndMenu();
			}
			ImGui::Text("");

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(" Render "))
		{
			if (ImGui::RadioButton(" Wireframe  ", isWireframe))
			{
				isWireframe = !isWireframe;
			}

			if (ImGui::RadioButton(" Bounding Boxes  ", isBoundingBoxes))
			{
				isBoundingBoxes = !isBoundingBoxes;
			}

			//TUDU: put rendering objects + maybe change the place to configuration
			if (ImGui::BeginMenu(" Camera Options "))
			{
				const char* listType[]{ "Perspective", "Orthographic" };

				ImGui::Text("");

				ImGui::Text(" Camera type:\t ");
				ImGui::SameLine();
				if (ImGui::Combo("##CameraType", &app->camera->cam->typeCameraSelected, listType, IM_ARRAYSIZE(listType)))
				{
					if (app->camera->cam->typeCameraSelected == 0)
						app->camera->cam->frustum.type = PerspectiveFrustum;

					if (app->camera->cam->typeCameraSelected == 1)
						app->camera->cam->frustum.type = OrthographicFrustum;
				}

				ImGui::Text("");

				//Fov camera
				ImGui::Text(" FOV\t\t\t  ");
				ImGui::SameLine();
				if (ImGui::SliderInt("##FOVert", &app->camera->cam->cameraFOV, 10, 200))
				{
					app->camera->cam->frustum.verticalFov = app->camera->cam->cameraFOV * DEGTORAD;
					app->camera->cam->frustum.horizontalFov = 2.0f * atanf(tanf(app->camera->cam->frustum.verticalFov / 2.0f) * 1.7f);
				}

				ImGui::Text("");

				//Slider Set Near Distane
				ImGui::Text(" Near Distance\t");
				ImGui::SameLine();
				if (ImGui::SliderFloat("##nearDistance", &app->camera->cam->nearDistance, 0.1f, app->camera->cam->farDistance))
				{
					app->camera->cam->frustum.nearPlaneDistance = app->camera->cam->nearDistance;
				}

				ImGui::Text("");

				//Input float Set Far Distane
				ImGui::Text(" Far Distance\t ");
				ImGui::SameLine();
				if (ImGui::InputFloat("##farDistance", &app->camera->cam->farDistance))
				{
					if (app->camera->cam->farDistance <= app->camera->cam->nearDistance)
					{
						app->camera->cam->nearDistance = app->camera->cam->farDistance;
					}

					app->camera->cam->frustum.farPlaneDistance = app->camera->cam->farDistance;
				}
				ImGui::Text("");

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);

		ImGui::EndMainMenuBar();
	}

	if (popUpAbout)
	{
		if(ImGui::Begin("About", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{ 
			ImGui::BulletText("The Seed Engine is a \ngame engine developed \nby Biel Rabasa and \nRoger Salas");
			ImGui::BulletText("To import files and \ntextures, drag and drop \nthe files");
			ImGui::BulletText("To move the camera visit \nour GitHub and check \nthe controls");

			ImGui::Text("");

			ImGui::BulletText("You can finde more in \nour GitHub");

			ImGui::End();
		}
	}

	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - 37);
	{
		//PLAY
		if (ImGui::ImageButton((ImTextureID)playButton, ImVec2(25, 25)))
		{
			if (app->IsStopped()) {
				app->SetState(GameState::PLAY);
				ImGui::SetWindowFocus("Game");
				playButton = stopTexture;
			}
			else {
				//STOP if in PLAY or PAUSE
				app->SetState(GameState::STOP);
				ImGui::SetWindowFocus("Scene");
				pauseButton = pausedTexture;
				playButton = playTexture;
			}
		}

		ImGui::SameLine();

		//PAUSE
		if (ImGui::ImageButton((ImTextureID)pauseButton, ImVec2(25, 25)))
		{
			if (app->IsPaused()) {
				app->SetState(GameState::PLAY);
				pauseButton = pausedTexture;
			}
			else if (app->IsRunning())
			{
				app->SetState(GameState::PAUSE);
				pauseButton = NOpausedTexture;
			}
		}

		ImGui::SameLine();

		//Increase speed
		if (ImGui::ImageButton((ImTextureID)speedButton, ImVec2(25, 25)))
		{
			if (app->timeSpeed == 1)
			{
				app->timeSpeed = 2.f;
				speedButton = speedx2;
			}
			else if (app->timeSpeed == 2.f)
			{
				app->timeSpeed = 4.f;
				speedButton = speedx3;
			}
			else if (app->timeSpeed == 4.f)
			{
				app->timeSpeed = 1.f;
				speedButton = speedx1;
			}
		}
	}
}

void HMenu::ThemeStylePopUp()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 4)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(colorWind[0], colorWind[1], colorWind[2], colorWind[3]));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(colorText[0], colorText[1], colorText[2], colorText[3]));
	}
}

void HMenu::ThemeStyleMenuBar()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 4)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(colorWind[0], colorWind[1], colorWind[2], colorWind[3]));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(colorText[0], colorText[1], colorText[2], colorText[3]));
	}
}

void HMenu::ThemeStyleWind()
{
	if (HMenu::colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.9, 0.9, 0.9, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (HMenu::colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 4)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(colorWind[0], colorWind[1], colorWind[2], colorWind[3]));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(colorText[0], colorText[1], colorText[2], colorText[3]));
	}
}

void HMenu::Init()
{
	playTexture = Application::GetInstance()->textures->LoadTexture("Resources/Icons/play_icon.png");
	stopTexture = Application::GetInstance()->textures->LoadTexture("Resources/Icons/stop_button.fbx.png");
	pausedTexture = Application::GetInstance()->textures->LoadTexture("Resources/Icons/pause_button.png");
	NOpausedTexture = Application::GetInstance()->textures->LoadTexture("Resources/Icons/unpause_button.png");
	speedx1 = Application::GetInstance()->textures->LoadTexture("Resources/Icons/vel1.png");
	speedx2 = Application::GetInstance()->textures->LoadTexture("Resources/Icons/vel2.png");
	speedx3 = Application::GetInstance()->textures->LoadTexture("Resources/Icons/vel3.png");


	playButton = playTexture;
	pauseButton = pausedTexture;
	speedButton = speedx1;
}

void HMenu::cleanUp()
{
	Application::GetInstance()->textures->DestroyTexture(playTexture);
	Application::GetInstance()->textures->DestroyTexture(stopTexture);
	Application::GetInstance()->textures->DestroyTexture(pausedTexture);
	Application::GetInstance()->textures->DestroyTexture(NOpausedTexture);
	Application::GetInstance()->textures->DestroyTexture(speedx1);
	Application::GetInstance()->textures->DestroyTexture(speedx2);
	Application::GetInstance()->textures->DestroyTexture(speedx3);

}
