#pragma once

#include "CelestialBody.h" 

class Planet : public CelestialBody
{
public:
	Planet(float bodySize, float rotSpeed, float orbRadius, float orbSpeed);
	void Update(float deltaTime) override;

private:
	float orbitRadius;
	float orbitSpeed;
	float currentOrbitAngle;
};

