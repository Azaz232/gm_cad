#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class CelestialBody
{
public:
	CelestialBody(float bodySize = 1.0f, float rotSpeed = 0.0f);

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void GenerateOrbit() {} 
	virtual void DrawOrbit();

	void InitAsSun();
	
	GLuint GetTextureLoader(const char* path);
	void SetTextureOverride(GLuint overrideTexId) { m_textureOverride = overrideTexId; }
	void ClearTextureOverride() { m_textureOverride = 0; }

	glm::vec3 GetPosition() const { return position; }

	virtual ~CelestialBody() = default;
private:

protected:
	float size;
	float rotationSpeed;
	float currentRotation;
	glm::vec3 position;
	int isSun = 0;

	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint indexCount = 0;
	GLuint textureId = 0;

	GLuint orbitVao = 0;
	GLuint orbitVbo = 0;
	GLuint orbitVertexCount = 0;

	GLuint LoadTexture(const char* path);
	GLuint m_textureOverride = 0; 

	glm::vec3 color = glm::vec3(1.0f);

	void GenerateSphere(int sectors, int stacks);
};
