#pragma once


#include "mesh.h"

class Cube : public Mesh
{
public:
	Cube() {};
	Cube(GLfloat length, GLfloat width, GLfloat depth) : length(length), width(width), depth(depth) { init(); }
	Cube(GLfloat length, GLfloat width, GLfloat depth, GLfloat textureU, GLfloat textureV) : length(length), width(width), depth(depth), textureScale(textureU, textureV) { init(); }

private:

	void init();
	GLfloat length;
	GLfloat width;
	GLfloat depth;
	glm::vec2 textureScale;
	glm::vec3 color;

};