#pragma once

#include <memory>
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "material.h"
#include "transform.h"

class SceneObject
{
public:
	//SceneObject() {};
	SceneObject() { }
	

	void addMesh(std::shared_ptr<Mesh> mesh);
	//void setTexture(Shader& shader, const char* fileName);
	void setMaterial(std::shared_ptr<Material> material);

	virtual void init();
	//virtual void destroy();
	virtual void render(Shader& shader);


	void rotate(const glm::vec3& rotation) { transform.rotate(rotation); }
	void translate(const glm::vec3& position) { transform.translate(position); }

	void setRotation(const glm::vec3& rotation) { transform.setRotation(rotation); }
	void setPosition(const glm::vec3& position) { transform.setPosition(position); }
	void setScale(const glm::vec3& scale) { transform.setScale(scale); }


protected:

	Transform transform;
	Shader shader;
	glm::vec3 position;
	//std::shared_ptr<Texture> texture;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;



};