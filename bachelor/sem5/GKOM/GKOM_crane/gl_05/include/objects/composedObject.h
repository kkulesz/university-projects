#pragma once
#include "sceneObject.h"

class ComposedObject : public SceneObject
{
public:
	ComposedObject(SceneObject* parent = nullptr)
	:SceneObject(parent) { }
	ComposedObject(std::shared_ptr<Material>material,  SceneObject* parent = nullptr)
		:SceneObject(material, parent) { }

	std::vector<std::shared_ptr<SceneObject>> objects;


	void addObject(std::shared_ptr<SceneObject> object)
	{
		object->setParent(this);
		objects.push_back(object);
		
	}

	void init() override;
	void render(Shader& shader) override;

};