#include "CelestialBody.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

const float PI = 3.14159265359f;

CelestialBody::CelestialBody(float bodySize, float rotSpeed)
{
    size = bodySize;
    rotationSpeed = rotSpeed;
    currentRotation = 0.0f;
    position = glm::vec3(0.0f); 

    GenerateSphere(36, 36);
}

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

    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void CelestialBody::GenerateSphere(int sectors, int stacks)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI / 2 - (float)i / stacks * PI;
        float xy = std::cos(stackAngle);
        float y = std::sin(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = (float)j / sectors * 2 * PI;

            float x = xy * std::cos(sectorAngle);
            float z = xy * std::sin(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectors + 1);    
        int k2 = k1 + sectors + 1;     

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    indexCount = static_cast<GLuint>(indices.size());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}