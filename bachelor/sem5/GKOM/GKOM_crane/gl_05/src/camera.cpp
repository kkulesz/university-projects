#include "../include/camera.h"
#include <iostream>
/*
Camera::Camera() {
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	updateHorizontalVectors();
	updateVerticalVectors();
}

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	cameraPosition = pos;
	cameraTarget = target;
	cameraUp = up;


	updateHorizontalVectors();
	updateVerticalVectors();
}

glm::vec3 Camera::getTarget() {
	return cameraTarget;
}

glm::vec3 Camera::getCameraPosition() {
	return cameraPosition;
}

glm::vec3 Camera::getCameraTarget() {
	return cameraTarget;
}

glm::vec3 Camera::getCameraUp() {
	return cameraUp;
}

void Camera::moveForward(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraMovementSpeedParameter * deltaTime;
	//std::cout << "Front:" << cameraFront.x << " " << cameraFront.y << " " << cameraFront.z << std::endl;
	//std::cout << "Right:" << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << std::endl;
	//std::cout << "Up:" << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;
	cameraPosition += cameraSpeed * cameraFront;
	cameraTarget += cameraSpeed * cameraFront;
}
void Camera::moveBackward(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraMovementSpeedParameter * deltaTime;
	cameraPosition -= cameraSpeed * cameraFront;
	cameraTarget -= cameraSpeed * cameraFront;
}
void Camera::moveRight(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraMovementSpeedParameter * deltaTime;
	cameraPosition += cameraRight * cameraSpeed;
	cameraTarget += cameraRight * cameraSpeed;
}
void Camera::moveLeft(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraMovementSpeedParameter * deltaTime;
	cameraPosition -= cameraRight * cameraSpeed;
	cameraTarget -= cameraRight * cameraSpeed;
}

void Camera::rotateRight(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraRotationSpeedParameter * deltaTime;
	cameraTarget += cameraRight * cameraSpeed;
	updateHorizontalVectors();
}

void Camera::rotateLeft(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraRotationSpeedParameter * deltaTime;
	cameraTarget -= cameraRight * cameraSpeed;
	updateHorizontalVectors();
}
void Camera::rotateUp(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraRotationSpeedParameter * deltaTime;
	cameraTarget += cameraUp * cameraSpeed;
	updateVerticalVectors();
}
void Camera::rotateDown(GLfloat deltaTime) {
	GLfloat cameraSpeed = cameraRotationSpeedParameter * deltaTime;
	cameraTarget -= cameraUp * cameraSpeed;
	updateVerticalVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}


void Camera::updateHorizontalVectors() {
	cameraFront = glm::normalize(cameraTarget - cameraPosition);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}
void Camera::updateVerticalVectors() {
	cameraFront = glm::normalize(cameraTarget - cameraPosition);
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}*/