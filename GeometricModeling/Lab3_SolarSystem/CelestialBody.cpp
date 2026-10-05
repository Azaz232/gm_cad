#include "CelestialBody.h"

#include <glm/gtc/matrix_transform.hpp> 

void CelestialBody::Update(float deltaTime)
{
    currentRotation += rotationSpeed * deltaTime;

    if (currentRotation > 360.0f)
    {
        currentRotation -= 360.0f;
    }
}

void CelestialBody::Draw()
{
    if (vao == 0) return;

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRotation), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size));

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}