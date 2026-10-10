#include "Comet.h"

#include <cmath>

Comet::Comet(float bodySize, float rotSpeed, float orbRadiusX, float orbRadiusZ, float orbSpeed)
{
	size = bodySize;
	rotationSpeed = rotSpeed;
	currentRotation = 0.0f;
	position = glm::vec3(0.0f);

	orbitRadiusX = orbRadiusX;
	orbitRadiusZ = orbRadiusZ;
	orbitSpeed = orbSpeed;
	currentOrbitAngle = 0.0f;
	color = glm::vec3(0.9f, 0.9f, 0.9f);

	GenerateSphere(36, 36);
}

void Comet::Update(float deltaTime)
{
	CelestialBody::Update(deltaTime);

	currentOrbitAngle += orbitSpeed * deltaTime;
	if (currentOrbitAngle > 360.0f)
	{
		currentOrbitAngle -= 360.0f;
	}

	float radians = glm::radians(currentOrbitAngle);

	position.x = orbitRadiusX * std::cos(radians);
	position.y = 0.0f;
	position.z = orbitRadiusZ * std::sin(radians);
}