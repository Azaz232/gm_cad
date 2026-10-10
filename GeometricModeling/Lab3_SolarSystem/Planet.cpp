#include "Planet.h"

#include <cmath>

Planet::Planet(float bodySize, float rotSpeed, float orbRadius, float orbSpeed)
{
	size = bodySize;
	rotationSpeed = rotSpeed;
	currentRotation = 0.0f;
	position = glm::vec3(0.0f);

	orbitRadius = orbRadius;
	orbitSpeed = orbSpeed;
	currentOrbitAngle = 0.0f;

	GenerateSphere(36, 36);
}

void Planet::Update(float deltaTime)
{
	CelestialBody::Update(deltaTime);

	currentOrbitAngle += orbitSpeed * deltaTime;

	if (currentOrbitAngle > 360.0f)
	{
		currentOrbitAngle -= 360.0f;
	}

	float radians = glm::radians(currentOrbitAngle);

	position.x = orbitRadius * std::cos(radians);
	position.y = 0.0f;
	position.z = orbitRadius * std::sin(radians);
}