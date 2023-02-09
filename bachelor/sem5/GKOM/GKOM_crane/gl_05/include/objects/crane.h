#pragma once
#include "composedObject.h"
#include "../cranePhysics.h"

#define CRANE_SPEED 0.3f	

class Crane : public ComposedObject
{
	CranePhysics physics;
public:
	Crane();
			
	


	void addObject(std::shared_ptr<SceneObject>);
	void drive(int);
	void turn(float);
	void moveFrontCrate(int);
	void moveRearCrate(int);
	void moveHook(int);
	void handBrake();
};


