#pragma once

class Mesh;

class Primitives
{
public:
	static Mesh* CreateCube();
	static Mesh* CreateSphere();
	static Mesh* CreateCylinder();
	static Mesh* CreatePlane();
};

