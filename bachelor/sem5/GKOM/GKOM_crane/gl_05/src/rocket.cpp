
#include "../include/rocket.h"
#include "../include/cylinder.h"
#include "../include/cylindricObject.h"
#include "../include/plane.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Rocket::init()
{

	std::shared_ptr<CylindricObject> ptr = std::make_shared<CylindricObject>(3.0f, 3.0f, 3.0f, 10, 1, shader);
	ptr->setPosition(glm::vec3(1.0f, 2.0f, -15.0f));
	std::shared_ptr<CylindricObject> ptr2 = std::make_shared<CylindricObject>(3.0f, 3.0f, 3.0f, 10, 1, shader);
	ptr2->setPosition(glm::vec3(-6.0f, 2.0f, -15.0f));
	std::shared_ptr<CylindricObject> ptr3 = std::make_shared<CylindricObject>(15.0f, 3.0f, 3.0f, 10, 1, shader);
	ptr3->setPosition(glm::vec3(-2.5f, 4.0f, -15.0f));
	ptr3->setRotation(glm::vec3(90.0, 0.0f, 0.0f));
	ptr->init();
	ptr2->init();
	ptr3->init();
	addObject(ptr);
	addObject(ptr2);
	addObject(ptr3);
	// setTexture(shader, "resources/dirt1.jpg");
	addMesh(std::make_shared<Cylinder>(2.0f, 2.0f, 2.0f, 3, 3));
	setMaterial(std::make_shared<Material>(
		std::make_shared<Texture>("resources/weiti.png"),
		std::make_shared<Texture>("resources/weiti.png"),
		32.0f
		));
	meshes.at(0)->start();

}



