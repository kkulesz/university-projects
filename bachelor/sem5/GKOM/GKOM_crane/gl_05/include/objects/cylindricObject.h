#pragma once
#include "sceneObject.h"
#include "../../include/meshes/cylinder.h"

class CylindricObject : public SceneObject
{
public:


	CylindricObject(float height, float baseRadius, float topRadius, 
		int segments, int stacks, std::shared_ptr<Material> material):
	height(height), baseRadius(baseRadius), topRadius(topRadius), segments(segments),
		stacks(stacks), SceneObject() {
		addMesh(std::make_shared<Cylinder>(height, baseRadius, topRadius, segments, stacks));
		setMaterial(material);
	}



private:
	GLfloat height;
	GLfloat baseRadius;
	GLfloat topRadius;
	GLint segments;
	GLint stacks;
};