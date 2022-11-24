#pragma once

class Mesh;
class GameObject;

enum class Shapes {
	EMPTY,
	CAMERA,
	PLANE,
	CUBE,
	SPHERE
};

class Primitives
{
public:
	static GameObject* CreatePrimitive(Shapes shape);

private:
	static Mesh* CreateCube();
	static Mesh* CreatePlane();
};

