#pragma once

#include "sceneObject.h"
#include "../meshes/cylinder.h"


class Rocket : public SceneObject
{
public:


	Rocket(std::string diffuseMapPath, std::string specularMapPath) : SceneObject()
	{
		addMesh(std::make_shared<Cylinder>(2.0f, 2.0f, 2.0f, 3, 3));
		setMaterial(std::make_shared<Material>(
			std::make_shared<Texture>(diffuseMapPath),
			std::make_shared<Texture>(specularMapPath),
			32.0f
			));
		setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}



};
