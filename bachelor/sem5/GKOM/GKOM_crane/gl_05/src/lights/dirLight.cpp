#include "../../include/lights/dirLight.h"


void DirLight::use(Shader& shader) {


	glUniform3f(glGetUniformLocation(shader.Program, ("dirLight.direction")), direction.x, direction.y, direction.z);

	
	glUniform3f(glGetUniformLocation(shader.Program, ("dirLight.lightColor")), lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(glGetUniformLocation(shader.Program, ("dirLight.ambient")), ambient.x, ambient.y, ambient.z);
	glUniform3f(glGetUniformLocation(shader.Program, ("dirLight.diffuse")), diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(glGetUniformLocation(shader.Program, ("dirLight.specular")), specular.x, specular.y, specular.z);

}

void DirLight::setDirection(glm::vec3 direction) {
	this->direction = direction;
}

glm::vec3 DirLight::getDirection() {
	return this->direction;
}