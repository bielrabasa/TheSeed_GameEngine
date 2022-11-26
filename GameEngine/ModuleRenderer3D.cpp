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
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

	InitFrameBuffer();	

	return ret;
}

bool ModuleRenderer3D::Start()
{
	// Projection matrix for
	//OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(App->camera->cam->GetProjetionMatrix());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->cam->GetViewMatrix());

	

	// light 0 on cam pos
	//lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	lights[0].SetPos(0, 0, 0);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	glBindFramebuffer(GL_FRAMEBUFFER, cameraBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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

	//Render Scene
	App->meshRenderer->RenderScene();

	if (mainGameCamera == nullptr) {
		LOG("No existing GAME camera");
	}
	else {
		//Only polygon fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Bind game camera framebuffer
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(mainGameCamera->GetProjetionMatrix());

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(mainGameCamera->GetViewMatrix());

		glBindFramebuffer(GL_FRAMEBUFFER, mainGameCamera->frameBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Render Game Camera
		App->meshRenderer->RenderGameWindow();
	}

	//FrameBuffer clean binding
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


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

	glDeleteFramebuffers(1, &frameBuffer);

	return true;
}

void ModuleRenderer3D::InitFrameBuffer()
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// generate texture
	glGenTextures(1, &cameraBuffer);
	glBindTexture(GL_TEXTURE_2D, cameraBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	float color[4] = { 0.1,0.1,0.1,0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cameraBuffer, 0);

	glGenRenderbuffers(1, &renderObjBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderObjBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderObjBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOGT(LogsType::WARNINGLOG, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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