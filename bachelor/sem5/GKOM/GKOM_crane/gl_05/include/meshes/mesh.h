#pragma once
#include <GL/glew.h>
#include "../Vertex.h"
#include <vector>

class Mesh
{

public:
	Mesh() {};
	std::vector<Vertex> getVertices() { return vertices; };
	std::vector<GLuint> getIndices() { return indices; };
	std::vector<Vertex> setVertices();
	std::vector<GLuint> setIndices();
	virtual void init() = 0;
	void start();
	void destroy();
	void render();


private:
	GLuint VBO, EBO, VAO;

protected:
	std::vector<GLuint> indices;
	std::vector<Vertex> vertices;


};