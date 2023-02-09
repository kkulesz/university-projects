#include <glm/gtc/matrix_transform.hpp>

#include "../include/transform.h"

Transform::Transform()
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

void Transform::setPosition(const glm::vec3& position)
{
	this->position = position;
}

void Transform::setRotation(const glm::vec3& rotation)
{
	this->rotation = rotation;
}

void Transform::setScale(const glm::vec3& scale)
{
	this->scale = scale;
}

void Transform::translate(const glm::vec3& position)
{
	this->position += position;
}

void Transform::rotate(const glm::vec3& rotation)
{
	this->rotation += rotation;
}

void Transform::move(const glm::vec3& displacement)
{
	this->position += displacement;
}



glm::vec3 Transform::getPosition()
{
	return position;
}

glm::vec3 Transform::getRotation()
{
	return rotation;
}

glm::vec3 Transform::getScale()
{
	return scale;
}



glm::mat4 Transform::getTransform()
{
	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::translate(transform, position);

	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	
	transform = glm::scale(transform, scale);

	return transform;
}