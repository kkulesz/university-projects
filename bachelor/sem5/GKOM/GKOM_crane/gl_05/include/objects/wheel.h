#pragma once
#include "composedObject.h"
#include "cylindricObject.h"

class Wheel : public ComposedObject 
{
public:
	Wheel(float height, float baseRadius, float topRadius,
		int segments, int stacks, std::shared_ptr<Material> material, std::shared_ptr<Material> tire_material)
	{

		std::shared_ptr<CylindricObject> wheel = std::make_shared<CylindricObject>(height, baseRadius, topRadius, segments, stacks, material);
		std::shared_ptr<CylindricObject> tire = std::make_shared<CylindricObject>(height - 0.01f, baseRadius + 0.01f, topRadius + 0.01f, segments, stacks, tire_material);
		addObject(wheel);
		addObject(tire);

	}
	
};