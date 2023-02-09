#include "../../include/meshes/cube.h"



void Cube::init()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 back = glm::vec3(0.0f, 0.0f, -1.0f);

	vertices.push_back(Vertex(glm::vec3(width / 2, -length / 2, -depth / 2), color, glm::vec2(0.0f, 0.0f) * textureScale, up));
	vertices.push_back(Vertex(glm::vec3(width / 2, -length / 2, depth / 2), color, glm::vec2(1.0f, 0.0f) * textureScale, up));
	vertices.push_back(Vertex(glm::vec3(width / 2, length / 2, depth / 2), color, glm::vec2(0.0f, 1.0f) * textureScale, down));
	vertices.push_back(Vertex(glm::vec3(width / 2, length / 2, -depth / 2), color, glm::vec2(1.0f, 1.0f) * textureScale, down));
	vertices.push_back(Vertex(glm::vec3(-width / 2, -length / 2, -depth / 2), color, glm::vec2(0.0f, 0.0f) * textureScale, right));
	vertices.push_back(Vertex(glm::vec3(-width / 2, -length / 2, depth / 2), color, glm::vec2(1.0f, 0.0f) * textureScale, left));
	vertices.push_back(Vertex(glm::vec3(-width / 2, length / 2, depth / 2), color, glm::vec2(0.0f, 1.0f) * textureScale, front));
	vertices.push_back(Vertex(glm::vec3(-width / 2, length / 2, -depth / 2), color, glm::vec2(1.0f, 1.0f) * textureScale, back));

	indices = { 
		0,1,2,
		0,2,3,
		3,2,6,
		7,3,6,
		4,5,6,
		4,6,7,
		4,0,5,
		0,1,5,
		1,6,2,
		1,5,6,
		4,0,3,
		4,3,7
	};
}