#pragma once

#include "mesh.h"

class Cuboid : public Mesh
{
public:

	Cuboid(float width, float height, float length) : width(width), height(height), length(length){ }

private:
	void init();

	std::vector<glm::vec3> getSideNormals();
	GLfloat width; //X
	GLfloat height;//Y
	GLfloat length;//Z
	
	glm::vec3 color;//to remove later
};