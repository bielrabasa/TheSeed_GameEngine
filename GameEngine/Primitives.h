#pragma once

class Mesh;
class GameObject;

enum class Shapes {
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
	static Mesh* CreateSphere();
	static Mesh* CreateCylinder();
	static Mesh* CreatePlane();
};

