#include "../include/material.h"



void Material::setDiffuseMap(std::shared_ptr<Texture> diffuseMap)
{
	this->diffuseMap = diffuseMap;
}

void Material::setSpecularMap(std::shared_ptr<Texture> specularMap)
{
	this->specularMap = specularMap;
}



std::shared_ptr<Texture> Material::getDiffuseMap()
{
	return this->diffuseMap;
}

std::shared_ptr<Texture> Material::getSpecularMap()
{
	return this->specularMap;
}

void Material::setShininess(float shininess) {
	this->shininess = shininess;
}

float Material::getShininess() {
	return this->shininess;
}

void Material::use(Shader& shader) {

	//glUniform3f(glGetUniformLocation(shader.Program, "material.ambient"), ambient.x, ambient.y, ambient.z);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, (*diffuseMap).LoadMipmapTexture(GL_TEXTURE0,(*diffuseMap).getFname()) );
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, (*specularMap).LoadMipmapTexture(GL_TEXTURE1, (*specularMap).getFname()));
	(*diffuseMap).use(shader,0);
	(*specularMap).use(shader,1);
	//glUniform3f(glGetUniformLocation(shader.Program, "material.diffuse"), diffuse.x, diffuse.y, diffuse.z);
	//glUniform3f(glGetUniformLocation(shader.Program, "material.specular"), specular.x, specular.y, specular.z);
	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), shininess);

}