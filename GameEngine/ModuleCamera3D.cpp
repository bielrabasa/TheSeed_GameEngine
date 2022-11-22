#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Transform.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	camState = CamStates::NORMAL;
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOGT(LogsType::SYSTEMLOG, "Setting up the camera");

	//Camera object
	cam = new CameraObject(true);
	cam->frustum.pos = float3(0, 0, -10);

	return true;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOGT(LogsType::SYSTEMLOG, "Cleaning camera");

	delete cam;

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	float3 newPos(0,0,0);
	Quat direction = Quat::identity;

	//Speed
	float sensitivity = 25.f * dt;
	float speed = 8.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed *= 2;

	//Mouse scrolls
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();
	int dw = -App->input->GetMouseZ(); //wheel


	//Camera states
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		camState = CamStates::FOCUSED;
	}
	else if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {
		camState = CamStates::FLYING;
	}
	else {
		camState = CamStates::NORMAL;
	}

	//Focus on object
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		//Look at object
		cam->LookAt(SelectedObjectPos());
	}

	//Camera states behaviour
	switch (camState) {

		//WASDQE + mouse "fps like" movement
	case CamStates::FLYING:
	{
		//WASDQE movement
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) cam->frustum.pos += cam->frustum.front * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) cam->frustum.pos -= cam->frustum.front * speed;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) cam->frustum.pos -= cam->frustum.WorldRight() * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) cam->frustum.pos += cam->frustum.WorldRight() * speed;

		//Move vertically independently of camera rotation
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) cam->frustum.pos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) cam->frustum.pos.y -= speed;

		//Rotate
		MouseRotation(dx, dy, sensitivity);
	}
	break;

	//Static cam, move arround reference
	case CamStates::FOCUSED:
	{
		cam->LookAt(SelectedObjectPos());

		//Calculate distance
		float len = float3(cam->reference - cam->frustum.pos).Length();

		//Rotate
		MouseRotation(dx, dy, sensitivity);

		//Go back to distance
		cam->frustum.pos = cam->reference + (cam->frustum.front * -len);
	}
	break;

	//(Mouse-wheel-click) move and (mouse-wheel-scroll) zoom
	case CamStates::NORMAL:
	{
		//Mouse Wheel click
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {
			cam->frustum.pos += cam->frustum.WorldRight() * (speed * dx / 2);
			cam->frustum.pos -= cam->frustum.up * (speed * dy / 2);
		}
		//Mouse wheel scroll
		if (dw != 0) {
			cam->frustum.pos += cam->frustum.front * speed * -dw;
		}
	}
	break;
	}

	return UPDATE_CONTINUE;
}

void ModuleCamera3D::MouseRotation(float dx, float dy, float sensitivity)
{
	//Rotation
	Quat dir;
	cam->frustum.WorldMatrix().Decompose(float3(), dir, float3());

	//Mouse look direction
	if (dx != 0)
	{
		float DeltaX = (float)dx * sensitivity;
		Quat X = Quat::identity;
		X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);
		dir = X * dir;
	}

	if (dy != 0)
	{
		float DeltaY = (float)dy * sensitivity;
		Quat Y = Quat::identity;
		Y.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DeltaY * DEGTORAD);
		dir = dir * Y;
	}

	//Set direction
	float4x4 rm = cam->frustum.WorldMatrix();
	rm.SetRotatePart(dir.Normalized());
	cam->frustum.SetWorldMatrix(rm.Float3x4Part());
}

float3 ModuleCamera3D::SelectedObjectPos()
{
	float3 SelectedObject = { 0,0,0 };
	if (App->hierarchy->selectedGameObj != nullptr) {
		SelectedObject = App->hierarchy->selectedGameObj->transform->getPosition(true);
	}
	return SelectedObject;
}