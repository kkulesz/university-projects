#include "../../include/lights/pointLight.h"

void PointLight::use(Shader& shader) {



	glUniform3f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].position").c_str()), lightPos.x, lightPos.y, lightPos.z);

	
	glUniform3f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].lightColor").c_str()), lightColor.x, lightColor.y, lightColor.z);


	glUniform3f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].ambient").c_str() ), ambient.x, ambient.y, ambient.z);
	glUniform3f(glGetUniformLocation(shader.Program, ("pointLights{" + std::to_string(lightIndex) + "].diffuse").c_str()), diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].specular").c_str()), specular.x, specular.y, specular.z);
	glUniform1f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].constant").c_str()), constant);
	glUniform1f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].linear").c_str()), linear);
	glUniform1f(glGetUniformLocation(shader.Program, ("pointLights[" + std::to_string(lightIndex) + "].quadratic").c_str()), quadratic);

}

void PointLight::setPosition(glm::vec3 position) {
	this->lightPos = position;
}

glm::vec3 PointLight::getPosition() {
	return this->lightPos;
}