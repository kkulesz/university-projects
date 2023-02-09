#pragma once
#include "objects/sceneObject.h"

#define MAX_WHEEL_SWING 35.0f
#define MAX_ACCELERATION 7.0f
#define BASE_SPEEDMULT 0.2f
#define ACCELERATION_STEP 0.02f
#define MAX_FORWARD_SPEED 0.4f
#define MAX_REAR_SPEED 0.1f
#define WHEEL_ROTATION 20
#define EPSILON 0.1f
#define MAX_HOOK_LINE_LENGTH 20.0f
#define MIN_HOOK_LINE_LENGTH 2.0f
#define HOOK_MOVE_SPEED 0.1f
#define MAX_FRONT_CRATE_SWING -20.0f
#define MIN_FRONT_CRATE_SWING -53.0f
#define MIN_REAR_CRATE_SWING 20.0f
#define MAX_REAR_CRATE_SWING 53.0f


class CranePhysics
{
	std::shared_ptr<Transform> transform;
	std::shared_ptr<SceneObject>
		frontCrate, rearCrate, crateLineBetween, crateLineFront, crateLineRear,
		hook1, hook2, load;
	std::vector<std::shared_ptr<SceneObject>> leftWheels;
	std::vector<std::shared_ptr<SceneObject>> rightWheels;
	float wheelswing = 0.0f;
	// te jeszcze nie wykorzystane - maksymalne wychylenie obu krat
	float crate1MaxSwing, crate1MinSwing, crate2MaxSwing, crate2MinSwing;
	float speedMult = 0.2f;
	float acceleration =0.0f;
	float crate1H, crate2H;
	
	float betweenLineLength;
	float frontLineLength, newFrontLineLength;
	float rearLineLenght;
	
	float prevRotationAngle;


public:
	void setTransform(std::shared_ptr<Transform> tr) { transform = tr; }//
	void setFrontCrate(std::shared_ptr<SceneObject> fc, float h) { frontCrate = fc; crate1H = h; }//
	void setRearCrate(std::shared_ptr<SceneObject> rc, float h) { rearCrate = rc; crate2H = h; }//
	// void setLeftWheel(std::shared_ptr<SceneObject> lw) { leftWheel = lw; }////
	// void setRightWheel(std::shared_ptr<SceneObject> rw) { rightWheel = rw; }//
	void setLineBetween(std::shared_ptr<SceneObject> lb, float bll) { crateLineBetween = lb; betweenLineLength = bll; }//
	void setFrontLine(std::shared_ptr<SceneObject> fl, float fll) { crateLineFront = fl; frontLineLength = fll; newFrontLineLength = fll; }//
	void setRearLine(std::shared_ptr<SceneObject> rl, float rll) { crateLineRear = rl; rearLineLenght = rll; }//
	void setHook1(std::shared_ptr<SceneObject> hk) { hook1 = hk; }
	void setHook2(std::shared_ptr<SceneObject> hk) { hook2 = hk; }
	void setLoad(std::shared_ptr<SceneObject> ld) { load = ld; }
	void addLeftWheel(std::shared_ptr<SceneObject> lw) { leftWheels.push_back(lw); }
	void addRightWheel(std::shared_ptr<SceneObject> rw) { rightWheels.push_back(rw); }



	void turn(float);
	void drive(int);
	void moveFrontCrate(int);
	void moveRearCrate(int);
	void updateLineBetween();
	void updateFrontLine();
	void updateRearLine();
	void moveHook(int);
	void handBrake();
	
};