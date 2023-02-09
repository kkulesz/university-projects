#pragma once

#include "composedObject.h"
#include "shader.h"

class Rocket : public ComposedObject
{
public:


	Rocket() : SceneObject() { position = glm::vec3(0.0f, 0.0f, 0.0f); }

	void init();


};