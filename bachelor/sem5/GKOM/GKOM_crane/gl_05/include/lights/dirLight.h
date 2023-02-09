#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "../shader.h"

class DirLight
{
public:

	DirLight( 
		glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		glm::vec3 lightColor,
		glm::vec3 direction) : 
		ambient(ambient), diffuse(diffuse), specular(specular),
		lightColor(lightColor), direction(direction) { }


	void use(Shader& shader);
	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
	glm::vec3 getColor() { return this->lightColor; };

private:


	glm::vec3 lightColor;

	glm::vec3 direction;


	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

};