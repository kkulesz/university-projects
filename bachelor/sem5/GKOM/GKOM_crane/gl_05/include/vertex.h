#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Vertex
{

public:
	Vertex() {};
	Vertex::Vertex(glm::vec3 crds, glm::vec3 clr, glm::vec2 tC, glm::vec3 n) : coordinates(crds), color(clr), textureCoordinates(tC), normalVector(n){}
	Vertex::Vertex(glm::vec3 crds, glm::vec2 tC, glm::vec3 n) : coordinates(crds), textureCoordinates(tC), normalVector(n) {}

private:
	glm::vec3 coordinates;
	glm::vec3 color;
	glm::vec2 textureCoordinates;
	glm::vec3 normalVector;


};
