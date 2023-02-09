#pragma once

#include <memory>
#include <glm/gtc/matrix_transform.hpp>

#include "../meshes/mesh.h"
#include "../shader.h"
#include "../material.h"
#include "../transform.h"
#include "../meshes/cube.h"

class SceneObject
{
public:
	SceneObject(SceneObject* parent = nullptr)
	:parent(parent)
	{
		transform = std::make_shared<Transform>();
	}

	SceneObject(std::shared_ptr<Material> material, SceneObject* parent = nullptr)
		: material(material), parent(parent)
	{
		transform = std::make_shared<Transform>();
	}
	

	void addMesh(std::shared_ptr<Mesh> mesh);
	void setMaterial(std::shared_ptr<Material> material);
	void setParent(SceneObject* parent);

	virtual void init()
	{
		meshes.at(0)->start();
	}
	virtual void render(Shader& shader);
	


	virtual void rotate(const glm::vec3& rotation) { transform->rotate(rotation); }
	virtual void move(const glm::vec3& displacement) { transform->move(displacement); }

	virtual void setRotation(const glm::vec3& rotation) { transform->setRotation(rotation); }
	virtual void setPosition(const glm::vec3& position) { transform->setPosition(position); }
	void setScale(const glm::vec3& scale) { transform->setScale(scale); }

	glm::vec3 getPosition() { return transform->getPosition(); }
	glm::vec3 getRotation() { return transform->getRotation(); }
	glm::vec3 getScale() { return transform->getScale(); }
	glm::mat4 makeLocalToWorld();

protected:

	
	std::shared_ptr<Transform> transform;
	std::vector<std::shared_ptr<Mesh> > meshes;
	std::shared_ptr<Material> material;
	SceneObject* parent;

};
