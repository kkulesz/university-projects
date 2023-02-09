#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>
#include "shader.h"
#include "texture.h"

class Material
{

public:
	Material(std::shared_ptr<Texture> diffuseMap, std::shared_ptr<Texture> specularMap, float shininess):
		diffuseMap(diffuseMap), specularMap(specularMap), shininess(shininess) { };



	void setDiffuseMap(std::shared_ptr<Texture> diffuseMap);
	void setSpecularMap(std::shared_ptr<Texture> specularMap);
	void setShininess(float shininess);
	std::shared_ptr<Texture> getDiffuseMap();
	std::shared_ptr<Texture> getSpecularMap();
	float getShininess();

	void use(Shader& shader);


private:
	std::shared_ptr<Texture> diffuseMap, specularMap;
	float shininess;


};