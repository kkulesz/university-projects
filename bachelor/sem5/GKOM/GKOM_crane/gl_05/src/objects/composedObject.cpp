#include "../../include/objects/composedObject.h"

void ComposedObject::render(Shader& shader )
{
	for (auto& object : objects) {
		
		object->render(shader);
	}
}

void ComposedObject::init()
{
	for (auto& object : objects) {

		object->init();
	}
}
