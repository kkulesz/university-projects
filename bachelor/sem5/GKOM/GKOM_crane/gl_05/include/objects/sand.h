#pragma once

#include "composedObject.h"
#include "cylindricObject.h"

class Sand : public ComposedObject
{
public:


	Sand(std::shared_ptr<Material> material) : ComposedObject(material) { initialize(); }
	Sand() : ComposedObject() {
		material = std::make_shared<Material>(
			std::make_shared<Texture>("resources/sand_color.png"),
			std::make_shared<Texture>("resources/dirt1specular.jpg"),
			32.0f);
		initialize();
	}

private:
	void initialize();

};