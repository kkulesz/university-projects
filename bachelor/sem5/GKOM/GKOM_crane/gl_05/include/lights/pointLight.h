#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "../shader.h"

class PointLight
{
public:

	PointLight(int lightIndex, 
		glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		GLfloat constant, GLfloat linear, GLfloat quadratic,
		glm::vec3 lightColor,
		glm::vec3 lightPos) :
		lightIndex(lightIndex),
		ambient(ambient), diffuse(diffuse), specular(specular),
		constant(constant), linear(linear), quadratic(quadratic),
		lightColor(lightColor), lightPos(lightPos){ }


	void use(Shader& shader);
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

private:


	int lightIndex;

	glm::vec3 lightColor;
	glm::vec3 lightPos;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;

};