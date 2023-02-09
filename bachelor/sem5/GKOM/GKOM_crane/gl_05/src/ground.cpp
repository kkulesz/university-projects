#include "../include/ground.h"
#include "../include/plane.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Ground::init()
{
	
	// setTexture(shader, "resources/dirt1.jpg");
	addMesh(std::make_shared<Plane>(1000.0f, 1000.0f, 1000.0f, 1000.0f));
	setMaterial(std::make_shared<Material>(
		std::make_shared<Texture>("resources/dirt1.jpg"),
		std::make_shared<Texture>("resources/dirt1.jpg"),
		32.0f
		));
	meshes.at(0)->start();//to tu
	//mesh->start();
}
