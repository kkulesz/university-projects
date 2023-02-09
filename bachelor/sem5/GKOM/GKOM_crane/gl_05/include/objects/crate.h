#pragma once
#include "composedObject.h"

#define CRATE_THICKNESS 0.05f

class Crate : public ComposedObject
{
private:
	float sideLength, height;
	int segments;
public:

	Crate(float sideLength, float height, int segments);
	void addObject(std::shared_ptr<SceneObject>);
};