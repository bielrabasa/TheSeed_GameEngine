#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();
	//LookAt(Reference);
	t = new Transform();
	t->setPosition(float3(0, 2, -5));
	t->setRotation(float3(0, -30, 0));
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOGT(LogsType::SYSTEMLOG, "Setting up the camera");
	bool ret = true;

	frustum = new Frustum();
	frustum->type = PerspectiveFrustum;
	frustum->nearPlaneDistance = 0.1f;
	frustum->farPlaneDistance = 500.f;
	frustum->front = float3::unitZ;
	frustum->up = float3::unitY;
	frustum->verticalFov = 60.0f * DEGTORAD;
	frustum->horizontalFov = 2.0f * atanf(tanf(frustum->verticalFov / 2.0f) * 1.7f);

	frustum->pos = float3(0, 0, -10);

	camState = CamStates::NORMAL;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOGT(LogsType::SYSTEMLOG, "Cleaning camera");
	delete t;
	delete frustum;
	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	//float3 newPos(0,0,0);
	//
	//Quat direction = Quat::identity;

	////Speed
	//float speed = 4.0f * dt;
	//if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	//	speed = 8.0f * dt;

	////Mouse scrolls
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();
	int dw = -App->input->GetMouseZ(); //wheel

	if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		frustum->pos += float3(dx, dy, 0);

	frustum->pos += float3(0, 0, dw);

	//float Sensitivity = speed / 6.0f;

	////Camera states
	//if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
	//	camState = CamStates::FOCUSED;
	//}
	//else if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {
	//	camState = CamStates::FLYING;
	//}
	//else {
	//	camState = CamStates::NORMAL;
	//}

	////Focus on object
	//if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) {
	//	//Look at object
	//	LookAt(SelectedObjectPos());
	//}

	////Camera states behaviour
	//switch (camState) {
	//
	////WASDQE + mouse "fps like" movement
	//case CamStates::FLYING:
	//	//Reference is same position, so i rotate on myself
	//	Reference = Position;
	//	
	//	//WASDQE movement
	//	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
	//	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;

	//	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
	//	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

	//		//Move vertically independently of camera rotation
	//	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) Move(float3(0, speed, 0));
	//	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) Move(float3(0, -speed, 0));

	//	//Mouse look direction
	//	if (dx != 0)
	//	{
	//		float DeltaX = (float)dx * Sensitivity * 10;
	//		Quat X = Quat::identity;
	//		X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX);
	//	}

	//	if (dy != 0)
	//	{
	//		float DeltaY = (float)dy * Sensitivity * 10;

	//		Y = rotate(Y, DeltaY, X);
	//		Z = rotate(Z, DeltaY, X);

	//		if (Y.y < 0.0f)
	//		{
	//			Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
	//			Y = cross(Z, X);
	//		}
	//	}

	//break;

	////Static cam, move arround reference
	//case CamStates::FOCUSED:
	//{
	//	Reference = SelectedObjectPos();
	//	Position -= Reference;

	//	//Mouse look direction
	//	if (dx != 0)
	//	{
	//		float DeltaX = (float)dx * Sensitivity * 10;

	//		X = rotate(X, DeltaX, float3(0.0f, 1.0f, 0.0f));
	//		Y = rotate(Y, DeltaX, float3(0.0f, 1.0f, 0.0f));
	//		Z = rotate(Z, DeltaX, float3(0.0f, 1.0f, 0.0f));
	//	}

	//	if (dy != 0)
	//	{
	//		float DeltaY = (float)dy * Sensitivity * 10;

	//		Y = rotate(Y, DeltaY, X);
	//		Z = rotate(Z, DeltaY, X);

	//		if (Y.y < 0.0f)
	//		{
	//			Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
	//			Y = cross(Z, X);
	//		}
	//	}

	//	Position = Reference + Z * length(Position);
	//}
	//break;

	////(Mouse-wheel-click) move and (mouse-wheel-scroll) zoom
	//case CamStates::NORMAL:
	//	//Mouse Wheel click
	//	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {

	//		newPos += X * dx * Sensitivity;
	//		newPos -= Y * dy * Sensitivity;

	//		Position += newPos;
	//		Reference += newPos;
	//	}
	//	//Mouse wheel scroll
		/*if (dw != 0) {
			newPos += Z * Sensitivity * dw * 10;*/
	//	}

	//break;
	//}

	//Position += newPos;
	//Reference += newPos;
	//
	//// Recalculate matrix -------------
	//CalculateViewMatrix();

	/*float3 p = t->getPosition();
	float sens = 10.0f;
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {

		p.y += dy * sens;
		p.x += dx * sens;
	}

	p.z += dw * sens;
	t->setPosition(p);*/

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference)
{
	/*this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(float3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();*/
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const float3& Spot)
{
	/*Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(float3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();*/
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	//float4x4 vm = frustum->ViewMatrix();
	viewMatrix = frustum->ViewMatrix();
	viewMatrix.Transpose();
	return viewMatrix.ptr();
	//return t->getLocalMatrix().Transposed().ptr();
	//return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	
	/*ViewMatrix = float4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);*/
}

float3 ModuleCamera3D::SelectedObjectPos()
{
	float3 SelectedObject = { 0,0,0 };
	if (App->hierarchy->selectedGameObj != nullptr) {
		//SelectedObject = App->hierarchy->selectedGameObj->transform->getPosition(true);
	}
	return SelectedObject;
}