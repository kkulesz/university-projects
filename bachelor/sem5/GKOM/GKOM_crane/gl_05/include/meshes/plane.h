#pragma once

#include "mesh.h"

class Plane : public Mesh
{
	
public:
	Plane() {};
	Plane(GLfloat length, GLfloat width) : length(length), width(width) { init(); }
	Plane(GLfloat length, GLfloat width, GLfloat textureU, GLfloat textureV ) : length(length), width(width), textureScale(textureU, textureV) { init(); }
	
private:
	void init();
	GLfloat length;
	GLfloat width;
	glm::vec2 textureScale;
	glm::vec3 color;

};
