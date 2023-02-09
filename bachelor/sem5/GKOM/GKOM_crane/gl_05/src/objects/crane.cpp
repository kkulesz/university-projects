#include "../../include/objects/crane.h"
#include "../../include/meshes/cylinder.h"
#include "../../include/objects/cylindricObject.h"
#include "../../include/objects/cuboidObject.h"
#include "../../include/objects/crate.h"
#include "../../include/objects/wheel.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#define WHEEL_RADIUS 1.0f
#define WHEEL_HEIHGT 0.5f
#define WHEEL_INIT_X_POSITION 0.0f
#define WHEEL_INIT_Z_POSITION 1.0f
#define WHEEL_X_SPACE 3.0f
#define WHEEL_Y_SPACE 2.0f

//chasis
#define CHASIS_WIDTH (2 * WHEEL_Y_SPACE - WHEEL_HEIHGT)
#define CHASIS_HEIGHT 0.5f
#define CHASIS_LENGTH 11.0f
#define CHASIS_POS_X (WHEEL_INIT_X_POSITION + 1.5f * WHEEL_X_SPACE)
#define CHASIS_POS_Y WHEEL_INIT_Z_POSITION
#define CHASIS_POS_Z 0.0f


//cabine
#define CABINE_WIDTH (2.0f * WHEEL_Y_SPACE - WHEEL_HEIHGT-0.01f)
#define CABINE_HEIGHT 5.0f
#define CABINE_LENGTH 4.0f
#define CABINE_POS_X (CHASIS_POS_X + 4.5f)
#define CABINE_POS_Y (CHASIS_POS_Y + CABINE_HEIGHT/2)
#define CABINE_POS_Z 0.0f

#define MIRROR_BASE_WIDTH 0.6f
#define MIRROR_BASE_HEIGHT 0.4f
#define MIRROR_BASE_LENGTH 0.1f
#define MIRROR_BASE_POS_X (CABINE_POS_X + CABINE_LENGTH/4)
#define MIRROR_BASE_POS_Y (CABINE_POS_Y + CABINE_HEIGHT/4)
#define MIRROR_BASE_POS_Z (CABINE_POS_Z + CABINE_WIDTH/2 + MIRROR_BASE_WIDTH/2)

#define MIRROR_WIDTH 0.9f
#define MIRROR_HEIGHT 1.5f
#define MIRROR_LENGTH 0.15f
#define MIRROR_POS_X (MIRROR_BASE_POS_X)
#define MIRROR_POS_Y (MIRROR_BASE_POS_Y+ MIRROR_HEIGHT/3)
#define MIRROR_POS_Z (MIRROR_BASE_POS_Z + MIRROR_BASE_WIDTH/2 + MIRROR_WIDTH/2 -0.4f)
#define MIRROR_ROT -30.0f

#define MIRROR_G_WIDTH (0.8f*MIRROR_WIDTH)
#define MIRROR_G_HEIGHT (0.8f*MIRROR_HEIGHT)
#define MIRROR_G_LENGTH 0.02f
#define MIRROR_G_POS_X (MIRROR_POS_X -MIRROR_LENGTH/2 - MIRROR_G_LENGTH/2)
#define MIRROR_G_POS_Y MIRROR_POS_Y
#define MIRROR_G_POS_Z MIRROR_POS_Z






//============trailer
#define TRAILER_WALL_HEIGHT 3.0f
#define TRAILER_WALL_WIDTH 0.3f


#define DOWN_PARTITION_WIDTH CHASIS_WIDTH
#define DOWN_PARTITION_HEIGHT 1.5f
#define DOWN_PARTITION_LENGTH (CHASIS_LENGTH- 2.0f)
#define DOWN_PARTITION_POS_X (CABINE_POS_X - CABINE_LENGTH/2 - DOWN_PARTITION_LENGTH/2)
#define DOWN_PARTITION_POS_Y (CHASIS_POS_Y + CHASIS_HEIGHT/2 + DOWN_PARTITION_HEIGHT/2 + 0.01f)
#define DOWN_PARTITION_POS_Z CHASIS_POS_Z

#define LEFT_PARTITION_WIDTH TRAILER_WALL_WIDTH
#define LEFT_PARTITION_HEIGHT TRAILER_WALL_HEIGHT
#define LEFT_PARTITION_LENGTH DOWN_PARTITION_LENGTH
#define LEFT_PARTITION_POS_X DOWN_PARTITION_POS_X
#define LEFT_PARTITION_POS_Y (CHASIS_POS_Y + CHASIS_HEIGHT/2 + DOWN_PARTITION_HEIGHT +  LEFT_PARTITION_HEIGHT/2 + 0.01f)
#define LEFT_PARTITION_POS_Z (CHASIS_POS_Z - CHASIS_WIDTH/2 + LEFT_PARTITION_WIDTH/2)

#define RIGHT_PARTITION_WIDTH TRAILER_WALL_WIDTH
#define RIGHT_PARTITION_HEIGHT TRAILER_WALL_HEIGHT
#define RIGHT_PARTITION_LENGTH DOWN_PARTITION_LENGTH
#define RIGHT_PARTITION_POS_X DOWN_PARTITION_POS_X
#define RIGHT_PARTITION_POS_Y (CHASIS_POS_Y + CHASIS_HEIGHT/2 + DOWN_PARTITION_HEIGHT + RIGHT_PARTITION_HEIGHT/2 + 0.01f)
#define RIGHT_PARTITION_POS_Z (CHASIS_POS_Z + CHASIS_WIDTH/2 - RIGHT_PARTITION_WIDTH/2)

#define FRONT_PARTITION_WIDTH (DOWN_PARTITION_WIDTH - RIGHT_PARTITION_WIDTH - LEFT_PARTITION_WIDTH)
#define FRONT_PARTITION_HEIGHT TRAILER_WALL_HEIGHT
#define FRONT_PARTITION_LENGTH TRAILER_WALL_WIDTH
#define FRONT_PARTITION_POS_X (DOWN_PARTITION_POS_X + LEFT_PARTITION_LENGTH/2 - FRONT_PARTITION_LENGTH/2)
#define FRONT_PARTITION_POS_Y (CHASIS_POS_Y + CHASIS_HEIGHT/2 + DOWN_PARTITION_HEIGHT + RIGHT_PARTITION_HEIGHT/2 + 0.01f)
#define FRONT_PARTITION_POS_Z (DOWN_PARTITION_POS_Z)

#define BACK_PARTITION_WIDTH (DOWN_PARTITION_WIDTH)
#define BACK_PARTITION_HEIGHT (DOWN_PARTITION_HEIGHT + LEFT_PARTITION_HEIGHT)
#define BACK_PARTITION_LENGTH TRAILER_WALL_WIDTH
#define BACK_PARTITION_POS_X (DOWN_PARTITION_POS_X - LEFT_PARTITION_LENGTH/2 - BACK_PARTITION_LENGTH/2)
#define BACK_PARTITION_POS_Y (CHASIS_POS_Y + CHASIS_HEIGHT/2 + BACK_PARTITION_HEIGHT/2)
#define BACK_PARTITION_POS_Z (DOWN_PARTITION_POS_Z)
//============trailer\\

//front glass
#define GLASS_WIDTH 3.0f
#define GLASS_HEIGHT (0.40f*CABINE_HEIGHT)
#define GLASS_LENGTH 0.03f
#define GLASS_POS_X (CABINE_POS_X + CABINE_LENGTH/2 + 0.02f)
#define GLASS_POS_Y (CABINE_POS_Y + CABINE_HEIGHT/2 - GLASS_HEIGHT + 0.25f)
#define GLASS_POS_Z 0.0f

#define FRONT_REGISTRATION_WIDTH (0.6f*CABINE_WIDTH)
#define FRONT_REGISTRATION_HEIGHT 0.5f
#define FRONT_REGISTRATION_LENGTH 0.03f
#define FRONT_REGISTRATION_POS_X (CABINE_POS_X + CABINE_LENGTH/2 + 0.02f)
#define FRONT_REGISTRATION_POS_Y (CABINE_POS_Y - CABINE_HEIGHT/4 - FRONT_REGISTRATION_HEIGHT-0.40f)
#define FRONT_REGISTRATION_POS_Z 0.0f


#define BACK_REGISTRATION_WIDTH (0.5f*CABINE_WIDTH)
#define BACK_REGISTRATION_HEIGHT 0.5f
#define BACK_REGISTRATION_LENGTH 0.03f
#define BACK_REGISTRATION_POS_X (DOWN_PARTITION_POS_X - DOWN_PARTITION_LENGTH/2 - BACK_REGISTRATION_LENGTH/2)
#define BACK_REGISTRATION_POS_Y DOWN_PARTITION_POS_Y
#define BACK_REGISTRATION_POS_Z 0.0f


#define EXHAUST_PIPE_RADIUS 0.2f
#define EXHAUST_PIPE_HEIGHT 3.5f
#define EXHAUST_PIPE_POS_X (CHASIS_POS_X - CHASIS_LENGTH/2)
#define EXHAUST_PIPE_POS_Y (CHASIS_POS_Y)
#define EXHAUST_PIPE_POS_Z (0.4f*CHASIS_WIDTH)



//poniżej całe rusztowanie
#define CRATE_BASE_RADIUS 1.25f
#define CRATE_BASE_HEIHGT 1.2f
#define CRATE_BASE_POS_X 0.0f
#define CRATE_BASE_POS_Y (DOWN_PARTITION_POS_Y + DOWN_PARTITION_HEIGHT - CRATE_BASE_RADIUS/2 + 0.3f)
#define CRATE_BASE_POS_Z 0.0f


#define CRATE_1_HEIGHT 30.0f
#define CRATE_1_SIDE_LENGTH 0.8f
#define CRATE_1_SEGMENTS 30
#define CRATE_1_POS_X CRATE_BASE_POS_X
#define CRATE_1_POS_Y CRATE_BASE_POS_Y
#define CRATE_1_POS_Z CRATE_BASE_POS_Z
#define CRATE_1_ROTATION -45.0f

#define CRATE_2_HEIGHT 12.0f
#define CRATE_2_SIDE_LENGTH 0.8f
#define CRATE_2_SEGMENTS 20
#define CRATE_2_POS_X CRATE_BASE_POS_X
#define CRATE_2_POS_Y CRATE_BASE_POS_Y//so that there is no colison with trailer
#define CRATE_2_POS_Z CRATE_BASE_POS_Z
#define CRATE_2_ROTATION 30.0f


#define CRATE_TOP_1_RADIUS 0.5f
#define CRATE_TOP_1_HEIHGT 0.9f
#define CRATE_TOP_1_POS_X 0.0f
#define CRATE_TOP_1_POS_Y (CRATE_1_HEIGHT/2)//bo jest wzgledem kraty
#define CRATE_TOP_1_POS_Z 0.0f

#define CRATE_TOP_2_RADIUS 0.5f
#define CRATE_TOP_2_HEIHGT 0.9f
#define CRATE_TOP_2_POS_X 0.0f
#define CRATE_TOP_2_POS_Y (CRATE_2_HEIGHT/2)//bo jest wzgledem kraty
#define CRATE_TOP_2_POS_Z 0.0f



#define BALAST_WIDTH 2.0f
#define BALAST_HEIGHT 2.0f
#define BALAST_LENGTH 2.0f
#define BALAST_POS_X (BACK_PARTITION_POS_X - BACK_PARTITION_LENGTH - BALAST_LENGTH - 1.0f)
#define BALAST_POS_Y 2.2f
#define BALAST_POS_Z 0.0f




/////////PONIZEJ JEST BRZYDKO
// liny są straszie napisana z palca i niegenerycznie, ale nie mam pomysłu jak by to zrobić
#define LINES_RADIUS 0.05f


#define LINE_1_RADIUS LINES_RADIUS
#define LINE_1_HEIHGT 9.5f
#define LINE_1_POS_X (BALAST_POS_X)
#define LINE_1_POS_Y (BALAST_POS_Y + 4.8f)
#define LINE_1_POS_Z (BALAST_POS_Z)
#define LINE_1_ROT_X 90.0f
#define LINE_1_ROT_Y 0.0f
#define LINE_1_ROT_Z 0.0f


#define LINE_2_RADIUS LINES_RADIUS
#define LINE_2_HEIHGT 15.45f
#define LINE_2_POS_X (CRATE_BASE_POS_X+2.9f)
#define LINE_2_POS_Y (CRATE_BASE_POS_Y + 10.1f)
#define LINE_2_POS_Z (CRATE_BASE_POS_Z)
#define LINE_2_ROT_X 90.0f
#define LINE_2_ROT_Y -82.75f
#define LINE_2_ROT_Z 0.0f


#define LINE_3_RADIUS LINES_RADIUS
#define LINE_3_HEIHGT 7.0f
#define LINE_3_POS_X (CRATE_BASE_POS_X + 10.75f)
#define LINE_3_POS_Y (CRATE_BASE_POS_Y + 7.5f)
#define LINE_3_POS_Z (CRATE_BASE_POS_Z)
#define LINE_3_ROT_X 90.0f
#define LINE_3_ROT_Y 0.0f
#define LINE_3_ROT_Z 0.0f


#define HOOK_1_WIDTH 0.3f
#define HOOK_1_HEIGHT 0.6f
#define HOOK_1_LENGTH 0.2f
#define HOOK_1_POS_X LINE_3_POS_X
#define HOOK_1_POS_Y (LINE_3_POS_Y - LINE_3_HEIHGT/2)
#define HOOK_1_POS_Z LINE_3_POS_Z

#define HOOK_2_WIDTH 0.3f
#define HOOK_2_HEIGHT 0.5f
#define HOOK_2_LENGTH 0.2f
#define HOOK_2_POS_X (HOOK_1_POS_X + 0.2f)
#define HOOK_2_POS_Y (HOOK_1_POS_Y -0.05f)
#define HOOK_2_POS_Z (HOOK_1_POS_Z)







Crane::Crane(): ComposedObject()
{

	physics.setTransform(transform);
	glm::vec3 startingPosition = this->getPosition();
	this->move(-startingPosition);


	//				kola
	std::vector<std::shared_ptr<Wheel>> wheels;
	std::shared_ptr<Material> material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/wheel.png"),
		std::make_shared<Texture>("resources/wheel.png"),
		32.0f);
	std::shared_ptr<Material> tire_material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/dirt1specular.jpg"),
		std::make_shared<Texture>("resources/dirt1specular.jpg"),
		32.0f);

	for (int i = 0; i < 8; i++)
	{
		wheels.push_back(std::make_shared<Wheel>(WHEEL_HEIHGT, WHEEL_RADIUS, WHEEL_RADIUS, 20, 1, material, tire_material));
	}
	//jeden bok dzwigu
	wheels.at(0)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION, WHEEL_INIT_Z_POSITION, WHEEL_Y_SPACE)); //przod, gora, prawo
	wheels.at(1)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION + WHEEL_X_SPACE, WHEEL_INIT_Z_POSITION, WHEEL_Y_SPACE)); //przod, gora, prawo
	wheels.at(2)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION + 2 * WHEEL_X_SPACE, WHEEL_INIT_Z_POSITION, WHEEL_Y_SPACE)); //przod, gora, prawo
	wheels.at(3)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION + 3 * WHEEL_X_SPACE, WHEEL_INIT_Z_POSITION, WHEEL_Y_SPACE)); //przod, gora, prawo
	//drugi bok dzwigu
	wheels.at(4)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION, WHEEL_INIT_Z_POSITION, -WHEEL_Y_SPACE)); //przod, gora, prawo
	wheels.at(5)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION + WHEEL_X_SPACE, WHEEL_INIT_Z_POSITION, -WHEEL_Y_SPACE)); //przod, gora, prawo
	wheels.at(6)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION + 2 * WHEEL_X_SPACE, WHEEL_INIT_Z_POSITION, -WHEEL_Y_SPACE)); //przod, gora, prawo
	wheels.at(7)->setPosition(glm::vec3(WHEEL_INIT_X_POSITION + 3 * WHEEL_X_SPACE, WHEEL_INIT_Z_POSITION, -WHEEL_Y_SPACE)); //przod, gora, prawo

	//polowa kol zwrocona w druga strone
	for (int i = wheels.size() / 2; i < wheels.size(); i++)
	{
		wheels.at(i)->setRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	}
	//teksturowanie kol i dodanie do sceny
	for (auto i = wheels.begin(); i != wheels.end(); i++)
	{
		//(*i)->setTexture("resources/kolo.png");
		addObject((*i));
	}
	for(int i=0;i<wheels.size();i++)
	{
		if (i < wheels.size() / 2)
		{
			physics.addLeftWheel(wheels.at(i));
		}
		else
			physics.addRightWheel(wheels.at(i));
	}


	// bottom of truck
	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/chasis.png"),
		std::make_shared<Texture>("resources/black.png"),
		32.0f);

	std::shared_ptr<CuboidObject> bottom = std::make_shared<CuboidObject>(CHASIS_LENGTH, CHASIS_HEIGHT, CHASIS_WIDTH, material); //dlugosc, wysokosc szerokosc
	bottom->setPosition(glm::vec3(CHASIS_POS_X, CHASIS_POS_Y, CHASIS_POS_Z));
	addObject(bottom);

	//cabine
	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/metal.jpg"),//metal.jpg//szrek.jpg
		std::make_shared<Texture>("resources/metal.jpg"),
		32.0f);
	std::shared_ptr<CuboidObject> cabine = std::make_shared<CuboidObject>(CABINE_LENGTH, CABINE_HEIGHT, CABINE_WIDTH, material); //dlugosc, wysokosc szerokosc
	cabine->setPosition(glm::vec3(CABINE_POS_X, CABINE_POS_Y, CABINE_POS_Z));
	addObject(cabine);

	std::shared_ptr<CuboidObject> right_base_mirror = std::make_shared<CuboidObject>(MIRROR_BASE_LENGTH, MIRROR_BASE_HEIGHT, MIRROR_BASE_WIDTH, material); //dlugosc, wysokosc szerokosc
	right_base_mirror->setPosition(glm::vec3(MIRROR_BASE_POS_X, MIRROR_BASE_POS_Y, MIRROR_BASE_POS_Z));
	addObject(right_base_mirror);

	std::shared_ptr<CuboidObject> right_mirror = std::make_shared<CuboidObject>(MIRROR_LENGTH, MIRROR_HEIGHT, MIRROR_WIDTH, material); //dlugosc, wysokosc szerokosc
	right_mirror->setPosition(glm::vec3(MIRROR_POS_X, MIRROR_POS_Y, MIRROR_POS_Z));
	right_mirror->setRotation(glm::vec3(0.0f, MIRROR_ROT, 0.0f));
	addObject(right_mirror);

	std::shared_ptr<CuboidObject> left_mirror_basse = std::make_shared<CuboidObject>(MIRROR_BASE_LENGTH, MIRROR_BASE_HEIGHT, MIRROR_BASE_WIDTH, material); //dlugosc, wysokosc szerokosc
	left_mirror_basse->setPosition(glm::vec3(MIRROR_BASE_POS_X, MIRROR_BASE_POS_Y, -MIRROR_BASE_POS_Z));
	addObject(left_mirror_basse);

	std::shared_ptr<CuboidObject> left_mirror = std::make_shared<CuboidObject>(MIRROR_LENGTH, MIRROR_HEIGHT, MIRROR_WIDTH, material); //dlugosc, wysokosc szerokosc
	left_mirror->setPosition(glm::vec3(MIRROR_POS_X, MIRROR_POS_Y, -MIRROR_POS_Z));
	left_mirror->setRotation(glm::vec3(0.0f, -MIRROR_ROT, 0.0f));
	addObject(left_mirror);

	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/mirror.jpg"),//metal.jpg//szrek.jpg
		std::make_shared<Texture>("resources/mirror.jpg"),
		32.0f);

	std::shared_ptr<CuboidObject> left_mirror_glass = std::make_shared<CuboidObject>(MIRROR_G_LENGTH, MIRROR_G_HEIGHT, MIRROR_G_WIDTH, material); //dlugosc, wysokosc szerokosc
	left_mirror_glass->setPosition(glm::vec3(MIRROR_G_POS_X, MIRROR_G_POS_Y, -MIRROR_G_POS_Z));
	left_mirror_glass->setRotation(glm::vec3(0.0f, -MIRROR_ROT, 0.0f));
	addObject(left_mirror_glass);

	std::shared_ptr<CuboidObject> right_mirror_glass = std::make_shared<CuboidObject>(MIRROR_G_LENGTH, MIRROR_G_HEIGHT, MIRROR_G_WIDTH, material); //dlugosc, wysokosc szerokosc
	right_mirror_glass->setPosition(glm::vec3(MIRROR_G_POS_X, MIRROR_G_POS_Y, MIRROR_G_POS_Z));
	right_mirror_glass->setRotation(glm::vec3(0.0f, MIRROR_ROT, 0.0f));
	addObject(right_mirror_glass);


	//front glass
	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/window.jpg"),
		std::make_shared<Texture>("resources/window.jpg"),
		32.0f);

	std::shared_ptr<CuboidObject> glass = std::make_shared<CuboidObject>(GLASS_LENGTH, GLASS_HEIGHT, GLASS_WIDTH, material); //dlugosc, wysokosc szerokosc
	glass->setPosition(glm::vec3(GLASS_POS_X, GLASS_POS_Y, GLASS_POS_Z));
	addObject(glass);


	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/essa2.png"),
		std::make_shared<Texture>("resources/metal.jpg"),
		32.0f);

	std::shared_ptr<CuboidObject> front_registration = std::make_shared<CuboidObject>(FRONT_REGISTRATION_LENGTH, FRONT_REGISTRATION_HEIGHT, FRONT_REGISTRATION_WIDTH, material); //dlugosc, wysokosc szerokosc
	front_registration->setPosition(glm::vec3(FRONT_REGISTRATION_POS_X, FRONT_REGISTRATION_POS_Y, FRONT_REGISTRATION_POS_Z));
	addObject(front_registration);

	std::shared_ptr<CuboidObject> back_registration = std::make_shared<CuboidObject>(BACK_REGISTRATION_LENGTH, BACK_REGISTRATION_HEIGHT, BACK_REGISTRATION_WIDTH, material); //dlugosc, wysokosc szerokosc
	back_registration->setPosition(glm::vec3(BACK_REGISTRATION_POS_X, BACK_REGISTRATION_POS_Y, BACK_REGISTRATION_POS_Z));
	addObject(back_registration);



	std::string trailerDiffuse = "resources/rust.jpg";//wood.png
	std::string trailerSpecular = "resources/black.png";//black.png
	material = std::make_shared<Material>(
		std::make_shared<Texture>(trailerDiffuse),
		std::make_shared<Texture>(trailerSpecular),
		32.0f);

	
	std::shared_ptr<CuboidObject> trailer_down = std::make_shared<CuboidObject>(
		DOWN_PARTITION_LENGTH, DOWN_PARTITION_HEIGHT, DOWN_PARTITION_WIDTH, material); //dlugosc, wysokosc szerokosc
	trailer_down->setPosition(glm::vec3(DOWN_PARTITION_POS_X, DOWN_PARTITION_POS_Y, DOWN_PARTITION_POS_Z));
	addObject(trailer_down);

	std::shared_ptr<CuboidObject> trailer_left = std::make_shared<CuboidObject>(
		LEFT_PARTITION_LENGTH, LEFT_PARTITION_HEIGHT, LEFT_PARTITION_WIDTH, material); //dlugosc, wysokosc szerokosc
	trailer_left->setPosition(glm::vec3(LEFT_PARTITION_POS_X, LEFT_PARTITION_POS_Y, LEFT_PARTITION_POS_Z));
	addObject(trailer_left);

	std::shared_ptr<CuboidObject> trailer_right = std::make_shared<CuboidObject>(
		RIGHT_PARTITION_LENGTH, RIGHT_PARTITION_HEIGHT, RIGHT_PARTITION_WIDTH, material); //dlugosc, wysokosc szerokosc
	trailer_right->setPosition(glm::vec3(RIGHT_PARTITION_POS_X, RIGHT_PARTITION_POS_Y, RIGHT_PARTITION_POS_Z));
	addObject(trailer_right);

	std::shared_ptr<CuboidObject> trailer_front = std::make_shared<CuboidObject>(
		FRONT_PARTITION_LENGTH, FRONT_PARTITION_HEIGHT, FRONT_PARTITION_WIDTH, material); //dlugosc, wysokosc szerokosc
	trailer_front->setPosition(glm::vec3(FRONT_PARTITION_POS_X, FRONT_PARTITION_POS_Y, FRONT_PARTITION_POS_Z));
	addObject(trailer_front);

	// std::shared_ptr<CuboidObject> trailer_back = std::make_shared<CuboidObject>(
	// 	BACK_PARTITION_LENGTH, BACK_PARTITION_HEIGHT, BACK_PARTITION_WIDTH, material); //dlugosc, wysokosc szerokosc
	// trailer_back->setPosition(glm::vec3(BACK_PARTITION_POS_X, BACK_PARTITION_POS_Y, BACK_PARTITION_POS_Z));
	// addObject(trailer_back);


	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/metal.jpg"),
		std::make_shared<Texture>("resources/black.png"),
		32.0f);

	std::shared_ptr<CylindricObject> crate_base = std::make_shared<CylindricObject>(
		CRATE_BASE_HEIHGT, CRATE_BASE_RADIUS, CRATE_BASE_RADIUS, 20, 1, material);
	crate_base->setPosition(glm::vec3(CRATE_BASE_POS_X, CRATE_BASE_POS_Y, CRATE_BASE_POS_Z));
	crate_base->setRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	addObject(crate_base);



	std::shared_ptr<Crate> crate1 = std::make_shared<Crate>(CRATE_1_SIDE_LENGTH, CRATE_1_HEIGHT, CRATE_1_SEGMENTS);
	crate1->setPosition(glm::vec3(CRATE_1_POS_X, CRATE_1_POS_Y, CRATE_1_POS_Z));
	crate1->rotate(glm::vec3(0, 0, CRATE_1_ROTATION));

	//crate->move(glm::vec3(-((CRATE_1_HEIGHT/2) * glm::sin(CRATE_1_ROTATION)),-((CRATE_1_HEIGHT/2) * glm::cos(CRATE_1_ROTATION)),0));
	addObject(crate1);
	physics.setFrontCrate(crate1,CRATE_1_HEIGHT+CRATE_TOP_1_RADIUS);


	std::shared_ptr<Crate> crate2 = std::make_shared<Crate>(CRATE_2_SIDE_LENGTH, CRATE_2_HEIGHT, CRATE_2_SEGMENTS);
	crate2->setPosition(glm::vec3(CRATE_2_POS_X, CRATE_2_POS_Y, CRATE_2_POS_Z));
	crate2->rotate(glm::vec3(0, 0, CRATE_2_ROTATION));

	//crate->move(glm::vec3(-((CRATE_1_HEIGHT/2) * glm::sin(CRATE_1_ROTATION)),-((CRATE_1_HEIGHT/2) * glm::cos(CRATE_1_ROTATION)),0));
	addObject(crate2);
	physics.setRearCrate(crate2,CRATE_2_HEIGHT + CRATE_TOP_2_RADIUS);


	std::shared_ptr<CylindricObject> crate_top_1 = std::make_shared<CylindricObject>(
		CRATE_TOP_1_HEIHGT, CRATE_TOP_1_RADIUS, CRATE_TOP_1_RADIUS, 20, 1, material);
	crate_top_1->setPosition(glm::vec3(CRATE_TOP_1_POS_X, CRATE_TOP_1_POS_Y, CRATE_TOP_1_POS_Z));
	crate_top_1->setRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	crate1->addObject(crate_top_1);

	std::shared_ptr<CylindricObject> crate_top_2 = std::make_shared<CylindricObject>(
		CRATE_TOP_2_HEIHGT, CRATE_TOP_2_RADIUS, CRATE_TOP_2_RADIUS, 20, 1, material);
	crate_top_2->setPosition(glm::vec3(CRATE_TOP_2_POS_X, CRATE_TOP_2_POS_Y, CRATE_TOP_2_POS_Z));
	crate_top_2->setRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	crate2->addObject(crate_top_2);


	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/kamien.jpg"),
		std::make_shared<Texture>(trailerSpecular),
		32.0f);
	std::shared_ptr<CuboidObject> balast = std::make_shared<CuboidObject>(
		BALAST_LENGTH, BALAST_HEIGHT, BALAST_WIDTH, material);//TODO: zmienić teksturę
	balast->setPosition(glm::vec3(BALAST_POS_X, BALAST_POS_Y, BALAST_POS_Z));
	addObject(balast);
	physics.setLoad(balast);



	std::string lineDiffuseMapPath = "resources/metal.jpg";
	std::string lineSpecularMapPath = "resources/negy.png";
	material = std::make_shared<Material>(
		std::make_shared<Texture>(lineDiffuseMapPath),
		std::make_shared<Texture>(lineSpecularMapPath),
		32.0f);
	std::shared_ptr<CylindricObject> line1 = std::make_shared<CylindricObject>(
		LINE_1_HEIHGT, LINE_1_RADIUS, LINE_1_RADIUS, 20, 1, material);
	line1->setPosition(glm::vec3(LINE_1_POS_X, LINE_1_POS_Y, LINE_1_POS_Z));
	line1->setRotation(glm::vec3(LINE_1_ROT_X, LINE_1_ROT_Y, LINE_1_ROT_Z));
	addObject(line1);
	physics.setRearLine(line1,LINE_1_HEIHGT);

	std::shared_ptr<CylindricObject> line2 = std::make_shared<CylindricObject>(
		LINE_2_HEIHGT, LINE_2_RADIUS, LINE_2_RADIUS, 20, 1, material);
	line2->setPosition(glm::vec3(LINE_2_POS_X, LINE_2_POS_Y, LINE_2_POS_Z));
	line2->setRotation(glm::vec3(LINE_2_ROT_X, LINE_2_ROT_Y, LINE_2_ROT_Z));
	addObject(line2);
	physics.setLineBetween(line2,LINE_2_HEIHGT);
	
	std::shared_ptr<CylindricObject> line3 = std::make_shared<CylindricObject>(
		LINE_3_HEIHGT, LINE_3_RADIUS, LINE_3_RADIUS, 20, 1, material);
	line3->setPosition(glm::vec3(LINE_3_POS_X, LINE_3_POS_Y, LINE_3_POS_Z));
	line3->setRotation(glm::vec3(LINE_3_ROT_X, LINE_3_ROT_Y, LINE_3_ROT_Z));
	addObject(line3);
	physics.setFrontLine(line3,LINE_3_HEIHGT);


	material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/metal.jpg"),
		std::make_shared<Texture>(lineSpecularMapPath),
		32.0f);
	std::shared_ptr<CuboidObject> hook1 = std::make_shared<CuboidObject>(
		HOOK_1_LENGTH, HOOK_1_HEIGHT, HOOK_1_WIDTH, material);//TODO: zmienić teksturę
	hook1->setPosition(glm::vec3(HOOK_1_POS_X, HOOK_1_POS_Y, HOOK_1_POS_Z));
	addObject(hook1);
	physics.setHook1(hook1);
	

	std::shared_ptr<CuboidObject> hook2 = std::make_shared<CuboidObject>(
		HOOK_2_LENGTH, HOOK_2_HEIGHT, HOOK_2_WIDTH, material);//TODO: zmienić teksturę
	hook2->setPosition(glm::vec3(HOOK_2_POS_X, HOOK_2_POS_Y, HOOK_2_POS_Z));

	hook2->setRotation(glm::vec3(0.0f, 0.0f, -45.0f));
	addObject(hook2);
	physics.setHook2(hook2);

	
	
	
	std::string pipeDiffuseMapPath = "resources/metal.jpg";
	std::string pipeSpecularMapPath = "resources/negy.png";
	material = std::make_shared<Material>(
		std::make_shared<Texture>(pipeDiffuseMapPath),
		std::make_shared<Texture>(pipeSpecularMapPath),
		32.0f);
	std::shared_ptr<CylindricObject> exhaust_pipe = std::make_shared<CylindricObject>(
		EXHAUST_PIPE_HEIGHT, EXHAUST_PIPE_RADIUS, EXHAUST_PIPE_RADIUS, 20, 1, material);
	exhaust_pipe->setPosition(glm::vec3(EXHAUST_PIPE_POS_X, EXHAUST_PIPE_POS_Y, EXHAUST_PIPE_POS_Z));
	exhaust_pipe->setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
	addObject(exhaust_pipe);
	std::shared_ptr<CylindricObject> exhaust_pipe2 = std::make_shared<CylindricObject>(
		EXHAUST_PIPE_HEIGHT, EXHAUST_PIPE_RADIUS, EXHAUST_PIPE_RADIUS, 20, 1, material);
	exhaust_pipe2->setPosition(glm::vec3(EXHAUST_PIPE_POS_X, EXHAUST_PIPE_POS_Y, EXHAUST_PIPE_POS_Z-EXHAUST_PIPE_RADIUS*2));
	exhaust_pipe2->setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
	addObject(exhaust_pipe2);
	
	this->move(startingPosition);
	physics.updateFrontLine();
	physics.updateLineBetween();
	physics.updateRearLine();

}

void Crane::addObject(std::shared_ptr<SceneObject> obj)
{
	obj->move(glm::vec3(-8,0,0));
	ComposedObject::addObject(obj);
}


// zaczalem wstawiac metody do jezdzenia
// domyslnie ma byc tak, ze dzwig jedzie do przodu do tylu tylko, w strone ta w ktora
// zwrocone sa jego kola (o ograniczonej osi obrotu)
// klikanie strzalek prawo/lewo wychyla kola w jedna strone
void Crane::drive(int direction)
{
	physics.drive(direction);
}

// tutaj jest cos nie tak, kiedy poruszamy obiektem nalezacym do ComposedObjectu
// to zostawia on swoj obraz w poczatkawej pozycji
void Crane::turn(float direction)
{
	physics.turn(direction);
}

void Crane::moveFrontCrate(int direction)
{
	physics.moveFrontCrate(direction);
}

void Crane::moveRearCrate(int direction)
{
	physics.moveRearCrate(direction);
}
void Crane::moveHook(int direction)
{
	physics.moveHook(direction);
}

void Crane::handBrake()
{
	physics.handBrake();
}
