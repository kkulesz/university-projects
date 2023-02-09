#include "../../include/objects/crate.h"
#include "../../include/objects/cylindricObject.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



Crate::Crate(float sideLength, float height, int segments): ComposedObject()
{
	this->sideLength = sideLength;
	this->height = height;
	this->segments = segments;
	std::string diffuseMapPath = "resources/metal.jpg";
	std::string specularMapPath = "resources/negy.png";
	std::shared_ptr<Material> material = std::make_shared<Material>(
		std::make_shared<Texture>(diffuseMapPath),
		std::make_shared<Texture>(specularMapPath),
		32.0f
		);
	
	std::shared_ptr<CylindricObject> pillar1;
	pillar1 = std::make_shared<CylindricObject>(height, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);
	std::shared_ptr<CylindricObject> pillar2;
	pillar2 = std::make_shared<CylindricObject>(height, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);
	std::shared_ptr<CylindricObject> pillar3;
	pillar3 = std::make_shared<CylindricObject>(height, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);
	std::shared_ptr<CylindricObject> pillar4;
	pillar4 = std::make_shared<CylindricObject>(height, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);



	pillar1->setPosition(glm::vec3(-sideLength / 2, 0, -sideLength / 2));
	pillar2->setPosition(glm::vec3(-sideLength / 2, 0, sideLength / 2));
	pillar3->setPosition(glm::vec3(sideLength / 2, 0, -sideLength / 2));
	pillar4->setPosition(glm::vec3(sideLength / 2, 0, sideLength / 2));

	pillar1->setRotation(glm::vec3(90, 0, 0));
	pillar2->setRotation(glm::vec3(90, 0, 0));
	pillar3->setRotation(glm::vec3(90, 0, 0));
	pillar4->setRotation(glm::vec3(90, 0, 0));


	addObject(pillar1);
	addObject(pillar2);
	addObject(pillar3);
	addObject(pillar4);

	float step = height / segments;
	float angle = atan(step / sideLength);
	float unitLength = 1 / (cos(angle)) * sideLength;

	for (int i = 0; i < segments; i++)
	{
		std::shared_ptr<CylindricObject> tmp = std::make_shared<CylindricObject>(
			unitLength, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);

		glm::vec3 pos(sideLength / 2, step / 2 - height / 2 + i * step, 0);
		tmp->setPosition(pos);
		if (i % 2 == 0)
		{
			tmp->setRotation(glm::vec3(-glm::degrees(angle), 0, 0));
		}
		else
		{
			tmp->setRotation(glm::vec3(glm::degrees(angle), 0, 0));
		}

		addObject(tmp);
	}

	for (int i = 0; i < segments; i++)
	{
		std::shared_ptr<CylindricObject> tmp = std::make_shared<CylindricObject>(
			unitLength, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);
		
		glm::vec3 pos(-sideLength / 2, step / 2 - height / 2 + i * step, 0);
		tmp->setPosition(pos);
		if (i % 2 == 0)
		{
			tmp->setRotation(glm::vec3(glm::degrees(angle), 0, 0));
		}
		else
		{
			tmp->setRotation(glm::vec3(-glm::degrees(angle), 0, 0));
		}
		addObject(tmp);
	}


	
	for (int i = 0; i < segments; i++)
	{
		std::shared_ptr<CylindricObject> tmp = std::make_shared<CylindricObject>(
			unitLength, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);

		glm::vec3 pos(0, step / 2 - height / 2 + i * step, sideLength / 2);
		tmp->setPosition(pos);

		if (i % 2 == 0)
		{
			tmp->setRotation(glm::vec3(90, 90 - glm::degrees(angle), 0));
			

		}
		else
		{
			tmp->setRotation(glm::vec3(90, 90 + glm::degrees(angle), 0));

			
		}

		addObject(tmp);
	}

	for (int i = 0; i < segments; i++)
	{
		std::shared_ptr<CylindricObject> tmp = std::make_shared<CylindricObject>(
			unitLength, CRATE_THICKNESS, CRATE_THICKNESS, 10, 1, material);

		glm::vec3 pos(0, step / 2 - height / 2 + i * step, -sideLength / 2);
		tmp->setPosition(pos);

		if (i % 2 == 0)
		{
			tmp->setRotation(glm::vec3(90, 90 - glm::degrees(angle), 0));

		}
		else
		{
			tmp->setRotation(glm::vec3(90, 90 + glm::degrees(angle), 0));

		}
		addObject(tmp);
	}

	// move(glm::vec3(0, height / 2, 0));
}

void Crate::addObject(std::shared_ptr<SceneObject> obj)
{
	obj->move(glm::vec3(0,height/2,0));
	ComposedObject::addObject(obj);
}


