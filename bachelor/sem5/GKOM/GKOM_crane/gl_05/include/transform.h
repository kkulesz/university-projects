#pragma once


#include <glm/glm.hpp>


class Transform
{
public:
	Transform();

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setScale(const glm::vec3& scale);
	void translate(const glm::vec3& position);
	void rotate(const glm::vec3& rotation);
	void move(const glm::vec3& displacement);
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	glm::mat4 getTransform();

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

};