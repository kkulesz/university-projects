#include "../include/cranePhysics.h"
#include <math.h>



void CranePhysics::turn(float direction)
{
	if(abs(wheelswing)<MAX_WHEEL_SWING)
	{

		if(direction>0)
		{
			if(leftWheels.at(3)->getRotation().y < MAX_WHEEL_SWING && (rightWheels.at(3)->getRotation().y -180.0f) < MAX_WHEEL_SWING)
			{
				leftWheels.at(3)->rotate(glm::vec3(0, direction, 0));
				rightWheels.at(3)->rotate(glm::vec3(0, direction, 0));
			}
		}
		else
		{
			if (leftWheels.at(3)->getRotation().y > -MAX_WHEEL_SWING && (rightWheels.at(3)->getRotation().y - 180.0f) > -MAX_WHEEL_SWING)
			{
				leftWheels.at(3)->rotate(glm::vec3(0, -abs(direction), 0));
				rightWheels.at(3)->rotate(glm::vec3(0, -abs(direction), 0));
			}
		}
		wheelswing += direction;
		

		if (abs(wheelswing)< EPSILON)
		{
			float rz = rightWheels.at(3)->getRotation().z;
			float lz = leftWheels.at(3)->getRotation().z;
			leftWheels.at(3)->setRotation(glm::vec3(0,0,lz));
			rightWheels.at(3)->setRotation(glm::vec3(0, 180, rz));
		}
	}
	else
	{
		if ((direction < 0 && wheelswing>=0) || (direction>0 && wheelswing<=0))
			wheelswing+=direction;

	}
	
}

void CranePhysics::drive(int direction)
{

	if (direction > 0)
	{
		if (acceleration <= MAX_FORWARD_SPEED)
			acceleration += ACCELERATION_STEP;
	}
	else if (direction < 0)
	{
		if (acceleration >= -MAX_REAR_SPEED)
			acceleration -= ACCELERATION_STEP;
	}
	else
	{
		if (acceleration < 0)
			acceleration += ACCELERATION_STEP / 2;
		else if (acceleration > 0)
			acceleration -= ACCELERATION_STEP / 2;

		if (abs(acceleration) < ACCELERATION_STEP)
			acceleration = 0;
	}
	
	float angle = transform->getRotation().y;
	
	if (acceleration > 0)
	{
		if (wheelswing > 0)
		{
			if (direction != 0)
			{
				transform->rotate(glm::vec3(0, 0.5, 0));
			}
			turn(-0.5);
		}
		else if (wheelswing < 0)
		{
			if (direction != 0)
			{
				transform->rotate(glm::vec3(0, -0.5, 0));
			}
			turn(0.5);
		}
		transform->move(acceleration * glm::vec3(glm::cos(glm::radians(angle)), 0, -glm::sin(glm::radians(angle))));

		//obrot kol
		for (auto& object : leftWheels) {

			object->rotate(glm::vec3(0, 0, -WHEEL_ROTATION *acceleration));
		}
		for (auto& object : rightWheels) {

			object->rotate(glm::vec3(0, 0, WHEEL_ROTATION *acceleration));
		}
	}
	else
	{
		if (wheelswing > 0)
		{
			if (direction != 0)
			{
				transform->rotate(glm::vec3(0, -0.5, 0));
				turn(-0.5);
			}
			
		}
		else if (wheelswing < 0)
		{
			if (direction != 0)
			{
				transform->rotate(glm::vec3(0, 0.5, 0));
				turn(0.5);
			}
			
		}
		
		
		transform->move(acceleration * glm::vec3(glm::cos(glm::radians(angle)), 0, -glm::sin(glm::radians(angle))));
		for (auto& object : leftWheels) {

			object->rotate(glm::vec3(0, 0, -WHEEL_ROTATION * acceleration));
		}
		for (auto& object : rightWheels) {

			object->rotate(glm::vec3(0, 0, WHEEL_ROTATION * acceleration));
		}
		
	}


}

void CranePhysics::moveFrontCrate(int direction)
{
	if (direction >= 0)
	{
		if (frontCrate->getRotation().z < MAX_FRONT_CRATE_SWING)
			frontCrate->rotate(glm::vec3(0, 0, 1));
	}
	else
	{
		if (frontCrate->getRotation().z > MIN_FRONT_CRATE_SWING)
			frontCrate->rotate(glm::vec3(0, 0, -1));
	}

	updateLineBetween();
	updateFrontLine();
}

void CranePhysics::moveRearCrate(int direction)
{
	if (direction >= 0)
	{
		if(rearCrate->getRotation().z <MAX_REAR_CRATE_SWING)
			rearCrate->rotate(glm::vec3(0, 0, 1));
	}
	else
	{
		if (rearCrate->getRotation().z > MIN_REAR_CRATE_SWING)
			rearCrate->rotate(glm::vec3(0, 0, -1));
	}
	
	updateLineBetween();
	updateRearLine();
}




void CranePhysics::updateLineBetween()
{
	float fAngle, rAngle;
	glm::vec3 fPos, rPos;
	fAngle = frontCrate->getRotation().z;
	rAngle = rearCrate->getRotation().z;
	
	fPos = glm::vec3(-glm::sin(glm::radians(fAngle)), glm::cos(glm::radians(fAngle)), 0);
	fPos *= crate1H;
	fPos += frontCrate->getPosition();
	
	rPos = glm::vec3(-glm::sin(glm::radians(rAngle)), glm::cos(glm::radians(rAngle)), 0);
	rPos *= crate2H;
	rPos += rearCrate->getPosition();
	
	glm::vec3 midPoint = 0.5f * (fPos+rPos);

	glm::vec3 diff = fPos - rPos;
	float newLength = glm::length(diff);
	
	float diffAngle = atan2(diff.x, diff.y);

	glm::vec3 prevRotation = crateLineBetween->getRotation();
	
	crateLineBetween->setScale(glm::vec3(1, 1,newLength/betweenLineLength ));
	crateLineBetween->setRotation(glm::vec3(prevRotation.x, -glm::degrees(diffAngle),prevRotation.z));
	crateLineBetween->setPosition(midPoint);
}
void CranePhysics::updateFrontLine()
{
	float fAngle;
	glm::vec3 fPos;
	fAngle = frontCrate->getRotation().z;


	fPos = glm::vec3(-glm::sin(glm::radians(fAngle)), glm::cos(glm::radians(fAngle)), 0);
	fPos *= crate1H;
	fPos += frontCrate->getPosition();
	
	crateLineFront->setPosition(fPos);
	hook1->setPosition(fPos);
	hook2->setPosition(fPos);

	crateLineFront->setScale(glm::vec3(1, 1, newFrontLineLength / frontLineLength));
	crateLineFront->move(glm::vec3(0,-newFrontLineLength /2,0));
	hook1->move(glm::vec3(0, -newFrontLineLength, 0));
	hook2->move(glm::vec3(0.2f, -newFrontLineLength, 0));

}

void CranePhysics::updateRearLine()
{
	float fAngle;
	glm::vec3 fPos;
	fAngle = rearCrate->getRotation().z;


	fPos = glm::vec3(-glm::sin(glm::radians(fAngle)), glm::cos(glm::radians(fAngle)), 0);
	fPos *= crate2H;
	fPos += rearCrate->getPosition();

	crateLineRear->setPosition(fPos);
	load->setPosition(fPos);
	crateLineRear->move(glm::vec3(0, -rearLineLenght / 2, 0));
	load->move(glm::vec3(0, -rearLineLenght, 0));
}


void CranePhysics::moveHook(int direction)
{
	if(direction>0)
	{
		if (newFrontLineLength < MAX_HOOK_LINE_LENGTH)
			newFrontLineLength+= HOOK_MOVE_SPEED;
	}
	else
	{
		if (newFrontLineLength > MIN_HOOK_LINE_LENGTH)
			newFrontLineLength -= HOOK_MOVE_SPEED;
	}
	updateFrontLine();
	
}

void CranePhysics::handBrake()
{
	acceleration = 0;
}
