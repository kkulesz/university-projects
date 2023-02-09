#include "../include/lampObject.h"
#include "../include/cube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void LampObject::init() {
	// setTexture(shader, "resources/weiti.png");
	addMesh(std::make_shared<Cube>(1.0f, 1.0f, 1.0f));
	setMaterial( std::make_shared<Material>(
		std::make_shared<Texture>("resources/weiti.png"),
		std::make_shared<Texture>("resources/weiti.png"),
		32.0f
		));
	
	meshes.at(0)->start(); //to tu

}