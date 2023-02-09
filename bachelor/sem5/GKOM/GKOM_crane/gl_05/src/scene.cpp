
#include "../include/scene.h"

//Scene::Scene(Shader& shader) : shader(shader) {}


void Scene::init()
{

	for (auto& cat : sceneObjects) {
		for (auto& obj : cat.second) {
			obj->init();
		}
	}

}

void Scene::render(std::string category, Shader& shader)
{
	
	for (auto& obj : sceneObjects[category]) {
		obj->render(shader);
	}
}

void Scene::addObject(std::string category, std::shared_ptr<SceneObject> sceneObject)
{
	sceneObjects[category].push_back(sceneObject);
}

void Scene::addShadingCategory(std::string category)
{
	sceneObjects[category] = std::vector<std::shared_ptr<SceneObject> >();
}

void Scene::setTransform(glm::mat4 trans)
{
	/*shader.Use();
	GLuint transformLoc = glGetUniformLocation(shader.Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
	
}
