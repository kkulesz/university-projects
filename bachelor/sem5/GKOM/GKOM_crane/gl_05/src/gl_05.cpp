#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <map>
//using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../include/skybox.h"
#include "../include/objects/ground.h"
#include "../include/lights/lampObject.h"
#include "../include/lights/pointLight.h"
#include "../include/lights/dirLight.h"

#include "../include/camera.h"
#include "../include/shader.h"
#include "../include/scene.h"
#include "../include/objects/cylindricObject.h"
#include "../include/objects/barrelStack.h"
#include "../include/objects/cuboidObject.h"
#include "../include/objects/crate.h"
#include "../include/objects/crane.h"
#include "../include/objects/sand.h"

const GLuint WIDTH = 1920, HEIGHT = 1080;
const GLuint SHADOW_WIDTH = 10000, SHADOW_HEIGHT = 10000;

//timing, needed to make the camera movement smooth
GLfloat deltaTime = 0.0f, 
		lastFrame = 0.0f;




std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
	for (int el = 0; el < 3; ++el)
	{
		std::cout << vec[el] << ' ';
		std::cout << std::endl;
	}
	return os;
}

#define NUMBER_OF_POINT_LIGHTS 6

Camera  camera(glm::vec3(0.0f, 3.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

std::shared_ptr<Crane> crane;

Camera_lock camera_lock = FREE;

bool mouselock = true;


// Moves/alters the camera positions based on user input
GLfloat lightIntensity = 1;
GLfloat dirLightAngle = 0;

void DoMovement()
{
	if(keys[GLFW_KEY_M])
	{
		mouselock = true;
	}
	if (keys[GLFW_KEY_N])
	{
		mouselock = false;
	}
	
	if (keys[GLFW_KEY_LEFT_SHIFT] || keys[GLFW_KEY_RIGHT_SHIFT])
	{
		deltaTime *= 4;
	}


	// Camera controls
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		// crane->move(speedMult * glm::vec3(0, 0, CRANE_SPEED));
		crane->turn(-2);
	}
	if (keys[GLFW_KEY_LEFT])
	{
		// crane->move(speedMult * glm::vec3(0, 0, -CRANE_SPEED));
		crane->turn(2);
	}
	
	if (keys[GLFW_KEY_UP])
	{
		crane->drive(1);

	}
	if (keys[GLFW_KEY_DOWN])
	{
		crane->drive(-1 );

	}
	if (!keys[GLFW_KEY_UP] && !keys[GLFW_KEY_DOWN])
	{
		crane->drive(0);
	}

	
	if (keys[GLFW_KEY_R])
	{
		crane->moveHook(1);
	
	}
	if (keys[GLFW_KEY_T])
	{
		crane->moveHook(-1);
	}
	
	if (keys[GLFW_KEY_Y])
	{
		crane->moveFrontCrate(1);
	}
	if (keys[GLFW_KEY_U])
	{
		crane->moveFrontCrate(-1);
	}
	if (keys[GLFW_KEY_H])
	{
		crane->moveRearCrate(1);
	}
	if (keys[GLFW_KEY_J])
	{
		crane->moveRearCrate(-1);
	}

	

	if (keys[GLFW_KEY_Z])
	{
		lightIntensity += 0.01;

	}

	if (keys[GLFW_KEY_X])
	{
		lightIntensity -= 0.01;

	}

	if (keys[GLFW_KEY_K])
	{
		dirLightAngle += 0.01;
		if (dirLightAngle >= 180)
		{
			dirLightAngle = -180;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		dirLightAngle -= 0.01;
		if (dirLightAngle <= -180)
		{
			dirLightAngle = 180;
		}
	}

	if (keys[GLFW_KEY_F1])
	{
		camera_lock = FREE;
	}
	if (keys[GLFW_KEY_F2])
	{
		camera_lock = LOCKED;
	}
	if(keys[GLFW_KEY_SPACE])
	{
		crane->handBrake();
	}
	
	if (camera_lock == LOCKED)
	{
		float xDis = crane->getRotation().y;
		float zDis = crane->getRotation().y;
		xDis = glm::cos(glm::radians(xDis));
		zDis = glm::sin(glm::radians(zDis));
		camera.setPosition(crane->getPosition() + glm::vec3(-7*xDis, 9, 7*zDis));
		// camera.
	}
}
// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset;
	GLfloat yOffset;
	if(mouselock)
	{
		xOffset = xPos - WIDTH / 2.0f;
		yOffset = HEIGHT / 2.0f - yPos;  // Reversed since y-coordinates go from bottom to left
	}
	else
	{
		xOffset = xPos - lastX;
		yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
	}
	
	lastX = xPos;
	lastY = yPos;
	if (keys[GLFW_KEY_LEFT_SHIFT])
	{
		// TODO: is it necessary to speed up camera rotation?
		xOffset *= 2;
		yOffset *= 2;
	}
	if(mouselock)
	{
		if (xPos == WIDTH / 2.0f && yPos == HEIGHT / 2.0f)
		{
			return;
		}
	}
	
	camera.ProcessMouseMovement(xOffset, yOffset);
	if(mouselock)
		glfwSetCursorPos(window, WIDTH / 2.0f, HEIGHT / 2.0f);
}




std::ostream& operator<<(std::ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			std::cout << mx[row][col] << ' ';
		std::cout << std::endl;
	}
	return os;
}





void sceneRender(Shader& theProgram, std::vector<PointLight> pointLights, 
	DirLight dirLight, Skybox skybox, Scene scene, glm::mat4& lightSpaceMatrix, unsigned int depthMap);

void lampRender(Shader& lampShader, Scene scene, DirLight dirLight);

void renderForShadow(Shader& theProgram, Scene scene, glm::mat4& lightSpaceMatrix);

void createBarrelStack(Scene& scene, glm::vec3 stackCenterPosition)
{
	std::shared_ptr<Material> material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/red.png"),
		std::make_shared<Texture>("resources/negy.png"),
		50.0f);
	for (int height = 1; height < 6; height++)
	{
		for (int x = height; x < 12 - height; x++)
		{
			std::shared_ptr<CylindricObject> cylinder = std::make_shared<CylindricObject>(7, 2, 2, 10, 10, material);
			(*cylinder).setPosition(glm::vec3(1.18f*x + 0.5f * ((int)height % 2) + stackCenterPosition.x,
				1.02f*height + stackCenterPosition.y - 0.5f, 0.0f + stackCenterPosition.z));
			(*cylinder).setScale(glm::vec3(0.3f, 0.3f, 0.3f));
			scene.addObject("main", cylinder);
		}

	}
}

void sceneSetup(Scene& scene)
{
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	(*ground).setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	scene.addObject("main", ground);


	// walls setup
	std::shared_ptr<Material> material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/sand-quarry2.jpg"),
		std::make_shared<Texture>("resources/sand-quarry2.jpg"),
		32.0f);
	std::shared_ptr<Ground> wall = std::make_shared<Ground>(material, 40.0f, 100.0f, 1.0f, 2.0f);
	wall->move(glm::vec3(0.0f, 0.0f, 50.0f));
	wall->rotate(glm::vec3(90.0f, 0.0f, 0.0f));
	scene.addObject("lamps", wall);


	wall = std::make_shared<Ground>(material, 40.0f, 100.0f, 1.0f, 2.0f);
	wall->move(glm::vec3(0.0f, 0.0f, -50.0f));
	wall->rotate(glm::vec3(90.0f, 0.0f, 0.0f));
	scene.addObject("lamps", wall);


	wall = std::make_shared<Ground>(material, 40.0f, 100.0f, 1.0f, 2.0f);
	wall->move(glm::vec3(50.0f, 0.0f, 0.0f));
	wall->rotate(glm::vec3(90.0f, 0.0f, 90.0f));
	scene.addObject("lamps", wall);


	wall = std::make_shared<Ground>(material, 40.0f, 100.0f, 1.0f, 2.0f);
	wall->move(glm::vec3(-50.0f, 0.0f, 0.0f));
	wall->rotate(glm::vec3(90.0f, 0.0f, 90.0f));
	scene.addObject("lamps", wall);



	//Dzwig
	crane = std::make_shared<Crane>();
	crane->move(glm::vec3(0, 0, 0));
	scene.addObject("main", crane);




	//barrel stacks
	std::vector<glm::vec3> stackCenterPositions = {
		glm::vec3(10.0f, 0.0f, -10.0f),
		glm::vec3(-10.0f, 0.0f, -10.0f),
		glm::vec3(-10.0f, 0.0f, -20.0f),
		glm::vec3(-23.0f, 0.0f, -27.0f),
		glm::vec3(24.0f, 0.0f, 14.0f),
		glm::vec3(23.0f, 0.0f, 18.0f),
		glm::vec3(22.0f, 0.0f, -14.0f),
		glm::vec3(-29.0f, 0.0f, 19.0f)
	};

	std::vector<glm::vec3> barrelStackRotations = {
		glm::vec3(0.0f,10.0f,  0.0f),
		glm::vec3(0.0f,-10.0f, 0.0f),
		glm::vec3(0.0f,-10.0f, 0.0f),
		glm::vec3(0.0f,-23.0f, 0.0f),
		glm::vec3(0.0f,24.0f,0.0f),
		glm::vec3(0.0f,23.0f, 0.0f),
		glm::vec3(0.0f,22.0f, 0.0f),
		glm::vec3(0.0f,-29.0f,0.0f)
	};

	std::shared_ptr<Material> barrel_material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/red.png"),
		std::make_shared<Texture>("resources/red.png"),
		32.0f);
	// createBarrelStack(scene, stackCenterPosition);
	for (int i = 0; i < stackCenterPositions.size(); i++)
	{
		glm::vec3 position = stackCenterPositions[i];
		glm::vec3 rotation = barrelStackRotations[i];
		std::shared_ptr<BarrelStack> barrelStack = std::make_shared<BarrelStack>(barrel_material);
		barrelStack->move(position);
		barrelStack->rotate(rotation);
		scene.addObject("main", barrelStack);
	}


	std::vector<glm::vec3> sand_centers = {
		glm::vec3(15.0f, 0.0f, -33.0f),
		glm::vec3(-33.0f, 0.0f, -1.0f),
		glm::vec3(-33.0f, 0.0f, -20.0f),
		glm::vec3(15.0f, 0.0f, 33.0f),
		glm::vec3(33.0f, 0.0f, 41.0f),
		glm::vec3(33.0f, 0.0f, -5.0f)
	};

	std::vector<glm::vec3> sand_rotations = {
		glm::vec3(-90.0f,0.0f,  180.0f),
		glm::vec3(-90.0f,0.0f, 40.0f),
		glm::vec3(-90.0f,0.0f,  180.0f),
		glm::vec3(-90.0f,0.0f, 7.0f),
		glm::vec3(-90.0f,0.0f, 70.0f),
		glm::vec3(-90.0f, 0.0f, 120.0f)

	};

	std::vector<glm::vec3> sand_scales = {
		glm::vec3(0.3f, 0.3f, 0.3f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(0.3f, 0.3f, 0.3f),
		glm::vec3(1.1f, 1.1f, 1.1f),
		glm::vec3(0.6f, 0.6f, 0.6f),
		glm::vec3(0.5f, 0.5f, 0.5f)
	};

	std::shared_ptr<Material> sand_material = std::make_shared<Material>(
		std::make_shared<Texture>("resources/sand_color.png"),
		std::make_shared<Texture>("resources/dirt1specular.jpg"),
		32.0f);
	// createBarrelStack(scene, stackCenterPosition);
	for (int i = 0; i < sand_centers.size(); i++)
	{
		glm::vec3 position = sand_centers[i];
		glm::vec3 rotation = sand_rotations[i];
		glm::vec3 scale = sand_scales[i];
		std::shared_ptr<Sand> sand = std::make_shared<Sand>(sand_material);

		sand->rotate(rotation);
		sand->move(position);
		sand->setScale(scale);
		scene.addObject("main", sand);
	}

}




int main()
{
	

	if (glfwInit() != GL_TRUE)
	{
		std::cout << "GLFW initialization failed" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - Dzwig kratownicowy", nullptr, nullptr);
		if (window == nullptr)
			throw std::exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);
		glEnable(GL_DEPTH_TEST);


		// Build, compile and link shader program
		Shader theProgram("shaders/multipleLights.vert", "shaders/multipleLights.frag");
		Shader lampShader("shaders/lamp.vert", "shaders/lamp.frag");
		Shader shadowShader("shaders/shadow.vert", "shaders/shadow.frag");



		// scene objects configuration
		Scene scene = Scene();
		scene.addShadingCategory("main");
		scene.addShadingCategory("lamps");


		// setup objects in scene
		sceneSetup(scene);

		
		
		Shader skyboxShader("shaders/skybox.vert", "shaders/skybox.frag");
		Skybox skybox = Skybox(skyboxShader);
		skybox.start();

	
		// lights setup
		std::vector<PointLight> pointLights;
		std::vector<glm::vec3> pointLightPositions = {
			glm::vec3(-5.0f,1.0f,5.0f),
			glm::vec3(5.0f,1.0f,5.0f),
			glm::vec3(15.0f,1.0f,5.0f),
			glm::vec3(-5.0f,1.0f,-5.0f),
			glm::vec3(5.0f,1.0f,-5.0f),
			glm::vec3(15.0f,1.0f,-5.0f),
		};
		for(int i=0; i<NUMBER_OF_POINT_LIGHTS; i++)
		{
			PointLight pointLight = PointLight(i,
				glm::vec3(0.2f, 0.2f, 0.2f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				1.0f, 0.09f, 0.032f,
				glm::vec3(1.0f, 1.0f, 1.0f),
				pointLightPositions[i]);
			pointLights.push_back(pointLight);
		}
		std::shared_ptr<Material> lampMaterial = std::make_shared<Material>(
			std::make_shared<Texture>("resources/weiti.png"),
			std::make_shared<Texture>("resources/weiti.png"),
			32.0f);
		for (int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++)
		{
			//can be merged into composed object
			std::shared_ptr<LampObject> lamp = std::make_shared<LampObject>();
			(*lamp).setPosition(pointLightPositions[i]);
			(*lamp).setScale(glm::vec3(0.3f, 0.3f, 0.3f));
			scene.addObject("lamps", lamp);

			
			std::shared_ptr<CuboidObject> lampBase = std::make_shared < CuboidObject > (0.2f,5.0f,0.2f, lampMaterial);
			(*lampBase).setPosition(pointLightPositions[i]-glm::vec3(0.0f,0.7f,0.0f));
			(*lampBase).setScale(glm::vec3(0.3f, 0.3f, 0.3f));
			scene.addObject("main", lampBase);
		}


		DirLight dirLight = DirLight( 
			glm::vec3(0.02f, 0.02f, 0.02f),
			glm::vec3(0.2f, 0.2f, 0.2f),
			glm::vec3(0.4f, 0.4f, 0.4f), 
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(-30.0f, -50.0f, 0.0f));

		scene.init();


		
		// shading
		unsigned int depthMapFBO;
		glGenFramebuffers(1, &depthMapFBO);

		unsigned int depthMap;

		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		

		// configure sampler2d indexes
		theProgram.Use();
		glUniform1i(glGetUniformLocation(theProgram.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(theProgram.Program, "material.specular"), 1);
		glUniform1i(glGetUniformLocation(theProgram.Program, "shadowMap"), 2);
		glUniform1i(glGetUniformLocation(lampShader.Program, "diffuse"), 0);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{

			
			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
			DoMovement();

			GLfloat lightDirX = - 30;
			GLfloat lightDirY = -10 * cos(dirLightAngle) - 50;
			GLfloat lightDirZ = -30 * sin(dirLightAngle);

			

			dirLight.setDirection(glm::vec3(lightDirX, lightDirY, lightDirZ));


			// dir light shadows
			float near_plane = 0.0f, far_plane = 200.0f;
			glm::mat4 lightProjection = glm::ortho(200.0f, -200.0f, -200.0f, 200.0f, near_plane, far_plane);
			glm::mat4 lightView = glm::lookAt(-dirLight.getDirection(),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 lightSpaceMatrix = lightProjection * lightView;
			lightSpaceMatrix = lightSpaceMatrix;
			
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);
			renderForShadow(shadowShader, scene, lightSpaceMatrix);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);


			

			// Clear the colorbuffer
			glViewport(0, 0, WIDTH, HEIGHT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			
			// lamps
			lampRender(lampShader, scene, dirLight);



			// main scene
			sceneRender(theProgram, pointLights, dirLight, skybox, scene, lightSpaceMatrix, depthMap);

			glfwSwapBuffers(window);
		}
	
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	glfwTerminate();

	return 0;
}

void renderForShadow(Shader& theProgram, Scene scene, glm::mat4& lightSpaceMatrix)
{
	theProgram.Use();
	glUniformMatrix4fv(glGetUniformLocation(theProgram.Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	glm::mat4 trans;
	trans = glm::mat4();



	// main uniform setup
	GLuint transformLoc = glGetUniformLocation(theProgram.Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	
	scene.render("main", theProgram);
}


void lampRender(Shader& lampShader, Scene scene, DirLight dirLight)
{
	// setup main transform, view and projection

	glm::mat4 trans;
	glm::mat4 view;
	glm::mat4 projection;

	view = camera.GetViewMatrix();
	projection = glm::perspective(camera.GetZoom(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	trans = glm::mat4();


	// lamp
	lampShader.Use();
	

	GLuint lampTransformLoc = glGetUniformLocation(lampShader.Program, "transform");
	GLuint lampViewLoc = glGetUniformLocation(lampShader.Program, "view");
	GLuint lampProjLoc = glGetUniformLocation(lampShader.Program, "projection");

	glUniformMatrix4fv(lampViewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(lampProjLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(glGetUniformLocation(lampShader.Program, "lightIntensity"), lightIntensity);
	glm::vec3 color = dirLight.getColor();
	glUniform3f(glGetUniformLocation(lampShader.Program, "lightColor"), color.x, color.y, color.z);



	scene.render("lamps", lampShader);
}

void sceneRender(Shader& theProgram, std::vector<PointLight> pointLights, 
	DirLight dirLight, Skybox skybox, Scene scene, glm::mat4& lightSpaceMatrix, unsigned int depthMap)
{
	theProgram.Use();
	glUniformMatrix4fv(glGetUniformLocation(theProgram.Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	glm::mat4 trans;
	glm::mat4 view;
	glm::mat4 projection;

	view = camera.GetViewMatrix();
	projection = glm::perspective(camera.GetZoom(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	trans = glm::mat4();

	
	// light source
	GLint viewPosLoc = glGetUniformLocation(theProgram.Program, "viewPos");
	glUniform1f(glGetUniformLocation(theProgram.Program, "lightIntensity"), lightIntensity);


	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


	for (int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++) {
		pointLights[i].use(theProgram);
	}

	dirLight.use(theProgram);





	// main uniform setup
	GLuint transformLoc = glGetUniformLocation(theProgram.Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	GLuint viewLoc = glGetUniformLocation(theProgram.Program, "view");
	GLuint projLoc = glGetUniformLocation(theProgram.Program, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));



	skybox.render(view, projection);
	
	theProgram.Use();

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, depthMap);	
	scene.render("main", theProgram);
}


