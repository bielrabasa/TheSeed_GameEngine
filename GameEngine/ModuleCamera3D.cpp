#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 0.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOGT(LogsType::SYSTEMLOG, "Setting up the camera");
	bool ret = true;

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

	vec3 newPos(0,0,0);
	
	//Speed
	float speed = 4.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	//Mouse scrolls
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();
	int dw = -App->input->GetMouseZ(); //wheel

	float Sensitivity = speed / 6.0f;

	//Focus on object
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) {
		LookAt(SelectedObject);
	}

	//Camera states
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		camState = FOCUSED;
	}
	else if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {
		camState = FLYING;
	}
	else {
		camState = NORMAL;
	}

	//Camera states behaviour
	switch (camState) {
	
	//WASDQE + mouse "fps like" movement
	case FLYING:
		//Reference is same position, so i rotate on myself
		Reference = Position;
		
		//WASDQE movement
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

			//Move vertically independently of camera rotation
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) Move(vec3(0, speed, 0));
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) Move(vec3(0, -speed, 0));

		//Mouse look direction
		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity * 10;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity * 10;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

	break;

	//Static cam, move arround reference
	case FOCUSED:
		
		//Mouse look direction
		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity * 10;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity * 10;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = SelectedObject + Z;
		Look(Position, SelectedObject);

	//No break, FOCUSED movement is added to the normal one

	//(Mouse-wheel-click) move and (mouse-wheel-scroll) zoom
	case NORMAL:
		//Mouse Wheel click
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT) {

			newPos += X * dx * Sensitivity;
			newPos -= Y * dy * Sensitivity;

			Position += newPos;
			Reference += newPos;
		}
		//Mouse wheel scroll
		if (dw != 0) {
			newPos += Z * Sensitivity * dw * 10;
		}

	break;
	}

	Position += newPos;
	Reference += newPos;
	/*if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
		
		

		if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) {
			if (!focused) {
				LookAt(vec3(0, 0, 0));
				focused = true;
			}
			else {
				Position -= Reference;

				if (dx != 0)
				{
					float DeltaX = (float)dx * Sensitivity;

					X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
					Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
					Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				}

				if (dy != 0)
				{
					float DeltaY = (float)dy * Sensitivity;

					Y = rotate(Y, DeltaY, X);
					Z = rotate(Z, DeltaY, X);

					if (Y.y < 0.0f)
					{
						Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
						Y = cross(Z, X);
					}
				}

				Position = Reference + Z * length(Position);
			}
		}
		else {
			//SHOULD SCROLL OVER
			
			
		}
	}
	
	//Mouse wheel zoom

	//Move arround
	
	if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		Position -= Reference;

		if(dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if(dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if(Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
	}
	*/
	
	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}