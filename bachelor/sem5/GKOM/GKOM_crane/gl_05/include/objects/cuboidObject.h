#pragma once

#include "sceneObject.h"
#include "../meshes/cuboid.h"

#include "../meshes/cuboid.h"


class CuboidObject : public SceneObject
{
public:
	CuboidObject( GLfloat w, GLfloat h, GLfloat l, std::shared_ptr<Material> material) : SceneObject() {
		setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		width = w;
		height = h;
		length = l;

		addMesh(std::make_shared<Cuboid>(width, height, length));
		setMaterial(material);

	};




private:
	GLfloat width;
	GLfloat height;
	GLfloat length;
};