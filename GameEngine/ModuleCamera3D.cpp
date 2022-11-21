#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	frustum.type = PerspectiveFrustum;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 500.f;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...

	frustum.pos = float3(0, 0, -10);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOGT(LogsType::SYSTEMLOG, "Setting up the camera");
	bool ret = true;

	camState = CamStates::NORMAL;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOGT(LogsType::SYSTEMLOG, "Cleaning camera");
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
		LookAt(SelectedObjectPos());
	}

	//Camera states behaviour
	switch (camState) {

		//WASDQE + mouse "fps like" movement
	case CamStates::FLYING:
	{
		//Reference is same position, so i rotate on myself
		//Reference = Position;

		//WASDQE movement
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) frustum.pos += frustum.front * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) frustum.pos -= frustum.front * speed;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) frustum.pos -= frustum.WorldRight() * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) frustum.pos += frustum.WorldRight() * speed;

		//Move vertically independently of camera rotation
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) frustum.pos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) frustum.pos.y -= speed;

		//Rotation
		Quat dir;
		frustum.WorldMatrix().Decompose(float3(), dir, float3());

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
		float4x4 rm = frustum.WorldMatrix();
		rm.SetRotatePart(dir.Normalized());
		frustum.SetWorldMatrix(rm.Float3x4Part());
	}
	break;

	//Static cam, move arround reference
	case CamStates::FOCUSED:
	{
		/*Reference = SelectedObjectPos();
		Position -= Reference;

		//Mouse look direction
		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity * 10;

			X = rotate(X, DeltaX, float3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, float3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, float3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity * 10;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
		*/
	}
	break;

	//(Mouse-wheel-click) move and (mouse-wheel-scroll) zoom
	case CamStates::NORMAL:
	{
		//Mouse Wheel click
		/*if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {

			newPos += X * dx * Sensitivity;
			newPos -= Y * dy * Sensitivity;

			Position += newPos;
			Reference += newPos;
		}
		//Mouse wheel scroll
		if (dw != 0) {
			newPos += Z * Sensitivity * dw * 10;
		}*/
	}
	break;
	}
	/*
	Position += newPos;
	Reference += newPos;
	
	

	float3 p = t->getPosition();
	float sens = 10.0f;
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

		p.y += dy * sens;
		p.x += dx * sens;
	}
	*/
	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference)
{
	frustum.pos = Position;
	reference = Reference;

	LookAt(reference);

	if(!RotateAroundReference)
	{
		reference = Position;
	}
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const float3& Spot)
{
	reference = Spot;
	frustum.front = (Spot - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}

void ModuleCamera3D::Move(const float3& Movement)
{
	frustum.pos += Movement;
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return viewMatrix.ptr();
}

float* ModuleCamera3D::GetProjetionMatrix()
{
	projectionMatrix = frustum.ProjectionMatrix();
	projectionMatrix.Transpose();
	return projectionMatrix.ptr();
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
}

float3 ModuleCamera3D::SelectedObjectPos()
{
	float3 SelectedObject = { 0,0,0 };
	if (App->hierarchy->selectedGameObj != nullptr) {
		SelectedObject = App->hierarchy->selectedGameObj->transform->getPosition(true);
	}
	return SelectedObject;
}