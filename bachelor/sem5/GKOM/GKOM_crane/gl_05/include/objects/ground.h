#pragma once

#include "sceneObject.h"
#include "../../include/meshes/plane.h"


class Ground : public SceneObject
{
public:


	Ground(
		std::shared_ptr<Material> material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/sandGround.jpg"),
		std::make_shared<Texture>("resources/dirt1specular.jpg"),
		32.0f),
		GLfloat length = 1000.0f, GLfloat width = 1000.0f, GLfloat textureU = 100.0f, GLfloat textureV = 100.0f		
	) : SceneObject()
	{
		addMesh(std::make_shared<Plane>(length, width, textureU, textureV));
		setMaterial(material);
		setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}


};