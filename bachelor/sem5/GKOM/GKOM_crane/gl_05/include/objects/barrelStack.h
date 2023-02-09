#pragma once
#include "composedObject.h"
#include "cylindricObject.h"

class BarrelStack : public ComposedObject
{
public:

	BarrelStack(std::shared_ptr<Material> material) : ComposedObject(material) { initialize(); }
	BarrelStack() : ComposedObject() {
		material = std::make_shared<Material>(
			std::make_shared<Texture>("resources/red.png"),
			std::make_shared<Texture>("resources/red.png"),
			32.0f);
		initialize();
	}

private:
	void initialize();



};