#include "Transform.h"

Transform::Transform(bool enabled) : Component(enabled) {
	type = ComponentType::TRANSFORM;
}

Transform::~Transform()
{
}

void Transform::PrintInspector()
{

}
