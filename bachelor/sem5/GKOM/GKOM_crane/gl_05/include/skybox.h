#pragma once

#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"


class Skybox
{

public:
	Skybox(Shader& shader) : skyboxShader(shader) {}
	void start();
	void render(glm::mat4 view, glm::mat4 projection);
	void destroy();

private:
	GLuint VAO, VBO;
	GLuint cubemapTexture;
	Shader skyboxShader;
	std::vector<std::string> faces;
	std::vector<GLfloat> vertices;
	void setBuffers();

};