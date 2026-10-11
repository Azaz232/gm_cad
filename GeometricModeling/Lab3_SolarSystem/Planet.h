#pragma once

#include "CelestialBody.h" 

class Planet : public CelestialBody
{
public:
	Planet(float bodySize, float rotSpeed, float orbRadius, float orbSpeed, glm::vec3 bodyColor = glm::vec3(1.0f));
	void Update(float deltaTime) override;
	void GenerateOrbit() override;

private:
	float orbitRadius;
	float orbitSpeed;
	float currentOrbitAngle;
};

