#include "../../include/objects/sand.h"
#include "../../include/meshes/cylinder.h"
#include "../../include/objects/cylindricObject.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Sand::initialize()
{
	std::shared_ptr<CylindricObject> ptr = std::make_shared<CylindricObject>(3.0f, 8.0f, 0.0f, 15, 1, material);
	ptr->setPosition(glm::vec3(10.0f, -2.0f, 1.5f)); //prawo, gora, przod

	std::shared_ptr<CylindricObject> ptr2 = std::make_shared<CylindricObject>(7.0f, 15.0f, 1.0f, 15, 1, material);
	ptr2->setPosition(glm::vec3(-6.0f, 0.0f, 3.5f));

	std::shared_ptr<CylindricObject> ptr3 = std::make_shared<CylindricObject>(4.0f, 9.0f, 0.3f, 15, 1, material);
	ptr3->setPosition(glm::vec3(-10.5f, 8.0f, 2.0f));


	addObject(ptr);
	addObject(ptr2);
	addObject(ptr3);
}