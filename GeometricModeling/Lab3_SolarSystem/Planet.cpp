#include "Planet.h"

#include <cmath>

Planet::Planet(float bodySize, float rotSpeed, float orbRadius, float orbSpeed, glm::vec3 bodyColor, const char* texturePath)
{
	size = bodySize;
	rotationSpeed = rotSpeed;
	currentRotation = 0.0f;
	position = glm::vec3(0.0f);

	orbitRadius = orbRadius;
	orbitSpeed = orbSpeed;
	currentOrbitAngle = 0.0f;
	color = bodyColor;
	isSun = 0;

	textureId = LoadTexture(texturePath);

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

void Planet::GenerateOrbit()
{
	const int pointsCount = 64; 
	orbitVertexCount = pointsCount;

	std::vector<float> orbitVertices;

	for (int i = 0; i < pointsCount; ++i)
	{
		float alpha = ((float)i / pointsCount) * 2.0f * 3.14159265359f;

		float x = orbitRadius * std::cos(alpha);
		float y = 0.0f;
		float z = orbitRadius * std::sin(alpha);

		orbitVertices.push_back(x);
		orbitVertices.push_back(y);
		orbitVertices.push_back(z);
	}
	glGenVertexArrays(1, &orbitVao);
	glGenBuffers(1, &orbitVbo);

	glBindVertexArray(orbitVao);

	glBindBuffer(GL_ARRAY_BUFFER, orbitVbo);
	glBufferData(GL_ARRAY_BUFFER, orbitVertices.size() * sizeof(float), orbitVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}