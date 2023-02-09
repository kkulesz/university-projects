#include <cmath>
#include <iostream>

#include "../../include/meshes/Cuboid.h"
#include <glm/glm.hpp>




void Cuboid::init() {
	//helper offsets
	GLfloat offX = width / 2;
	GLfloat offY = height / 2;
	GLfloat offZ = length / 2;

	glm::vec3 v1 = glm::vec3(-offX, -offY, -offZ);
	glm::vec3 v2 = glm::vec3(-offX, -offY, offZ);
	glm::vec3 v3 = glm::vec3(offX, -offY, offZ);
	glm::vec3 v4 = glm::vec3(offX, -offY, -offZ);

	glm::vec3 v5 = glm::vec3(-offX, offY, -offZ);
	glm::vec3 v6 = glm::vec3(-offX, offY, offZ);
	glm::vec3 v7 = glm::vec3(offX, offY, offZ);
	glm::vec3 v8 = glm::vec3(offX, offY, -offZ);



	//so that texture is displayed correctly
	glm::vec2 uv1 = glm::vec2(0.0f, 0.0f);
	glm::vec2 uv2 = glm::vec2(1.0f, 0.0f);
	glm::vec2 uv3 = glm::vec2(1.0f, 1.0f);
	glm::vec2 uv4 = glm::vec2(0.0f, 1.0f);

	glm::vec3 down =	glm::vec3( 0.0f, -1.0f,  0.0f);
	glm::vec3 left =	glm::vec3(-1.0f,  0.0f,  0.0f);
	glm::vec3 forward = glm::vec3( 0.0f,  0.0f,  1.0f);
	glm::vec3 right =	glm::vec3( 1.0f,  0.0f,  0.0f);
	glm::vec3 back =	glm::vec3( 0.0f,  0.0f, -1.0f);
	glm::vec3 up =		glm::vec3( 0.0f,  1.0f,  0.0f);




	//down square
	vertices.push_back(Vertex(v1, uv1, down));
	vertices.push_back(Vertex(v2, uv2, down));
	vertices.push_back(Vertex(v3, uv3, down));
	vertices.push_back(Vertex(v4, uv4, down));

	//left
	vertices.push_back(Vertex(v1, uv1, left));
	vertices.push_back(Vertex(v5, uv2, left));
	vertices.push_back(Vertex(v6, uv3, left));
	vertices.push_back(Vertex(v2, uv4, left));

	//forward
	vertices.push_back(Vertex(v2, uv1, forward));
	vertices.push_back(Vertex(v6, uv2, forward));
	vertices.push_back(Vertex(v7, uv3, forward));
	vertices.push_back(Vertex(v3, uv4, forward));

	//right
	vertices.push_back(Vertex(v3, uv1, right));
	vertices.push_back(Vertex(v7, uv2, right));
	vertices.push_back(Vertex(v8, uv3, right));
	vertices.push_back(Vertex(v4, uv4, right));

	//backward
	vertices.push_back(Vertex(v4, uv1, back));
	vertices.push_back(Vertex(v8, uv2, back));
	vertices.push_back(Vertex(v5, uv3, back));
	vertices.push_back(Vertex(v1, uv4, back));


	//up square
	vertices.push_back(Vertex(v8, uv1, up));
	vertices.push_back(Vertex(v7, uv2, up));
	vertices.push_back(Vertex(v6, uv3, up));
	vertices.push_back(Vertex(v5, uv4, up));


	// indeksy w kolejnosci takiej,zeby normalne byly na zewnatrz
	for (int i = 0; i < 6; ++i) {
		//first triangle
		indices.push_back(i * 4);
		indices.push_back(i * 4 + 1);
		indices.push_back(i * 4 + 2);
		//second
		indices.push_back(i * 4 + 2);
		indices.push_back(i * 4 + 3);
		indices.push_back(i * 4 );
	}
	
}
