#include "../../include/meshes/plane.h"



void Plane::init()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(Vertex(glm::vec3(-width / 2, 0, -length / 2), color, glm::vec2(0.0f, 0.0f) * textureScale, up));
	vertices.push_back(Vertex(glm::vec3(width / 2, 0, -length / 2), color, glm::vec2(1.0f, 0.0f) * textureScale, up));
	vertices.push_back(Vertex(glm::vec3(-width / 2, 0, length / 2), color, glm::vec2(0.0f, 1.0f) * textureScale, up));
	vertices.push_back(Vertex(glm::vec3(width / 2, 0, length / 2), color, glm::vec2(1.0f, 1.0f) * textureScale, up));
	indices = { 0, 1, 2, 1, 2, 3 };	
}