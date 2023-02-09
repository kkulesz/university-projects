#pragma once


#include "../meshes/cube.h"
#include "../objects/sceneObject.h"

class LampObject: public SceneObject
{
public:

	LampObject() : SceneObject()
	{
		addMesh(std::make_shared<Cube>(1.0f, 1.0f, 1.0f));
		setMaterial(std::make_shared<Material>(
			std::make_shared<Texture>("resources/negy.png"),
			std::make_shared<Texture>("resources/negy.png"),
			32.0f
			));
		setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	};



private:

};
