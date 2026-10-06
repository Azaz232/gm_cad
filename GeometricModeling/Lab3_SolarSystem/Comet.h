#pragma once

#include "CelestialBody.h"

class Comet : public CelestialBody
{
public:
	Comet(float bodySize, float rotSpeed, float orbRadiusX, float orbRadiusZ, float orbSpeed);
	void Update(float deltaTime) override;
private:
	float orbitRadiusX;
	float orbitRadiusZ;

	float orbitSpeed;
	float currentOrbitAngle;
};

