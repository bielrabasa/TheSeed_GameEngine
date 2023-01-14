#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

#include "ModuleDummy.h"
#include "ComponentCamera.h"
#include "HeaderMenu.h"

#include "SDL_opengl.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */


ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ProjectionMatrix.SetIdentity();
	mainGameCamera = nullptr;
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOGT(LogsType::SYSTEMLOG, "Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOGT(LogsType::WARNINGLOG, "OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	//GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		LOGT(LogsType::WARNINGLOG, "Error: %a\n", glewGetErrorString(err));
	}
	else {
		LOGT(LogsType::SYSTEMLOG, "Using Glew %s", glewGetString(GLEW_VERSION));
	}

	LOGT(LogsType::SYSTEMLOG, "Vendor: %s", glGetString(GL_VENDOR));
	LOGT(LogsType::SYSTEMLOG, "Renderer: %s", glGetString(GL_RENDERER));
	LOGT(LogsType::SYSTEMLOG, "OpenGL version supported %s", glGetString(GL_VERSION));
	LOGT(LogsType::SYSTEMLOG, "GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//App->dummy->AddDebug(("Vendor: %s", glGetString(GL_VENDOR)));
	//

	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOGT(LogsType::WARNINGLOG, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOGT(LogsType::WARNINGLOG, "Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOGT(LogsType::WARNINGLOG, "Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color


		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOGT(LogsType::WARNINGLOG, "Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		//lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].ambient.Set(1.f, 1.f, 1.f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}
	
	//Imgui
	ImGui_Logic::App = this->App;
	ImGui_Logic::Init();

	return ret;
}

bool ModuleRenderer3D::Start()
{
	ImGui_Logic::Start();
	return true;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	//App->meshRenderer->RenderUIWindow();

	// light 0 on cam pos
	//lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	lights[0].SetPos(0, 0, 0);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Imgui
	ImGui_Logic::NewFrame();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	// Scene camera already set during all the frame


	//Wireframe option
	if (HMenu::isWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	BindCameraBuffer(App->camera->cam);
	//Render Meshes
	App->meshRenderer->RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Render GAME CAMERA
	if (mainGameCamera != nullptr) {
		//Only polygon fill
	

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//mainGameCamera->frustum.type = PerspectiveFrustum;
		//mainGameCamera->frustum.nearPlaneDistance = nearDistance;
		//mainGameCamera->frustum.farPlaneDistance = farDistance; //inspector
		//mainGameCamera->frustum.front = float3::unitZ;
		//mainGameCamera->frustum.up = float3::unitY;
		//mainGameCamera->frustum.verticalFov = cameraFOV * DEGTORAD;
		//mainGameCamera->frustum.horizontalFov = 2.0f * atanf(tanf(mainGameCamera->frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...
		//mainGameCamera->frustum.pos = float3(0, 0, 0);
		//Bind buffer
		BindCameraBuffer(mainGameCamera);

		//Render Game Camera
		App->meshRenderer->RenderGameWindow();

		App->ui->BindUIBuffer();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	//FrameBuffer clean binding


	//Imgui
	ImGui_Logic::Render();

	SDL_GL_SwapWindow(App->window->window);
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOGT(LogsType::SYSTEMLOG, "Destroying 3D Renderer");

	//Imgui
	ImGui_Logic::CleanUp();

	if (context != NULL)
	{
		SDL_GL_DeleteContext(context);
	}

	return true;
}

void ModuleRenderer3D::BindCameraBuffer(CameraComponent* cc)
{
	//Bind game camera framebuffer
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(cc->GetProjetionMatrix());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cc->GetViewMatrix());

	glBindFramebuffer(GL_FRAMEBUFFER, cc->frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void ModuleRenderer3D::DrawBox(float3* corners, float3 color)
{
	//Fill points
	int indices[24] = { 0,2,2,6,6,4,4,0,0,1,1,3,3,2,4,5,6,7,5,7,3,7,1,5 };

	glBegin(GL_LINES);
	glColor3fv(color.ptr());

	for (size_t i = 0; i < 24; i++)
	{
		glVertex3fv(corners[indices[i]].ptr());
	}

	glColor3f(255.f, 255.f, 255.f);
	glEnd();
}

void ModuleRenderer3D::DrawLine(float3 a, float3 b, float3 color)
{
	glBegin(GL_LINES);

	glColor3fv(color.ptr());


	glVertex3fv(a.ptr());
	glVertex3fv(b.ptr());

	glColor3f(255.f, 255.f, 255.f);

	glEnd();
}

void ModuleRenderer3D::SetMainCamera(CameraComponent* cam)
{
	//No main camera
	if (cam == nullptr) {
		mainGameCamera = nullptr;
		LOGT(LogsType::WARNINGLOG, "No existing GAME camera");
		return;
	}

	//Switch main cameras
	if(mainGameCamera != nullptr)
		mainGameCamera->isMainCamera = false;

	cam->isMainCamera = true;

	mainGameCamera = cam;
}

CameraComponent* ModuleRenderer3D::GetMainCamera()
{
	return mainGameCamera;
}