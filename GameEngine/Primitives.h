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

enum class UIShapes {
	CANVA,
	FONS,
	UIBUTTON,
	UICHECKBOX,
	INPUTBOX
};

class Primitives
{
public:
	static GameObject* CreatePrimitive(Shapes shape);

	static GameObject* CreateUIObjects(UIShapes UIshape);

	static Mesh* CreateCube();
	static Mesh* CreatePlane();
private:

};

