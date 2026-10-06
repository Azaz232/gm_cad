#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float startDistance = 25.0f);

	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(int direction, float deltaTime);
	void ProcessMouse(float yOffset);
private:
	glm::vec3 position; 
	glm::vec3 target; 
	glm::vec3 up;

	float yaw;
	float distance;

	void UpdateCameraPosition();
};
