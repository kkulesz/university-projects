#pragma once

#include "shader.h"
#include "objects/sceneObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <map>

class Scene
{
public:
	Scene() {};

	void init();
	void render(std::string category, Shader& shader);
	void addShadingCategory(std::string category);
	void addObject(std::string category, std::shared_ptr<SceneObject> sceneObject);
	void setTransform(glm::mat4 trans);

private:
	
	//std::vector<std::shared_ptr<SceneObject> >  sceneObjects;
	std::map<std::string,  std::vector<std::shared_ptr<SceneObject> > > sceneObjects;
};