#include "../../include/objects/sceneObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void SceneObject::addMesh(std::shared_ptr<Mesh> mesh)
{
	mesh->init();
	meshes.push_back(mesh);
}


void SceneObject::render(Shader& shader)
{
	material->use(shader);
	glm::mat4 trans;
	if (!parent)
		trans = transform->getTransform();
	else
	{
		trans = parent->makeLocalToWorld() * transform->getTransform();
	}
	
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	meshes.at(0)->render();
	trans = glm::mat4();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
}


void SceneObject::setMaterial(std::shared_ptr<Material> mat)
{
	material = mat;
}

void SceneObject::setParent(SceneObject* parentTransform)
{
	this->parent = parentTransform;
}


glm::mat4 SceneObject::makeLocalToWorld()
{
	if(!parent)
	{
		return transform->getTransform();
	}
	return parent->makeLocalToWorld() *transform->getTransform();
}

