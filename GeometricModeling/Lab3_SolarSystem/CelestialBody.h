#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class CelestialBody
{
public:
	CelestialBody(float bodySize = 1.0f, float rotSpeed = 0.0f);

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual ~CelestialBody() = default;
private:

protected:
	float size;
	float rotationSpeed;
	float currentRotation;
	glm::vec3 position;

	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint indexCount = 0;
	GLuint textureId = 0;

	glm::vec3 color = glm::vec3(1.0f);

	void GenerateSphere(int sectors, int stacks);
};
