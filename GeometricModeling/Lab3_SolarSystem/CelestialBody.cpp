#include "CelestialBody.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

const float PI = 3.14159265359f;

CelestialBody::CelestialBody(float bodySize, float rotSpeed)
{
    size = bodySize;
    rotationSpeed = rotSpeed;
    currentRotation = 0.0f;
    position = glm::vec3(0.0f); 
    color = glm::vec3(1.0f);
}

void CelestialBody::InitAsSun()
{
    color = glm::vec3(2.0f, 0.85f, 0.2f); 
    GenerateSphere(36, 36); 

    textureId = LoadTexture("textures/sun.jpg");
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
    glUniform3f(glGetUniformLocation(currentProgram, "objectColor"), color.r, color.g, color.b);

    GLuint activeTex = (m_textureOverride != 0) ? m_textureOverride : textureId;

    if (activeTex != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, activeTex);
        glUniform1i(glGetUniformLocation(currentProgram, "texture_diffuse"), 0);
        glUniform1i(glGetUniformLocation(currentProgram, "hasTexture"), 1);
    }
    else
    {
        glUniform1i(glGetUniformLocation(currentProgram, "hasTexture"), 0);
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void CelestialBody::DrawOrbit()
{
    if (orbitVao == 0) return;

    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glUniform3f(glGetUniformLocation(currentProgram, "objectColor"), 0.7f, 0.7f, 0.7f);

    glUniform1i(glGetUniformLocation(currentProgram, "hasTexture"), 0);

    glBindVertexArray(orbitVao);
    glDrawArrays(GL_LINE_LOOP, 0, orbitVertexCount);
    glBindVertexArray(0);
}

void CelestialBody::GenerateSphere(int sectors, int stacks)
{
    if (vao != 0) glDeleteVertexArrays(1, &vao);
    if (vbo != 0) glDeleteBuffers(1, &vbo);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI / 2 - (float)i / stacks * PI;
        float xy = std::cos(stackAngle);
        float y = std::sin(stackAngle);

        float v = (float)i / stacks;

        for (int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = (float)j / sectors * 2 * PI;

            float x = xy * std::cos(sectorAngle);
            float z = xy * std::sin(sectorAngle);

            float u = (float)j / sectors;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back(u);
            vertices.push_back(v);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &ebo);
}

GLuint CelestialBody::LoadTexture(const char* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1) format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA; 

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        std::cout << "Successfully loaded texture: " << path << std::endl;
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        textureID = 0;
    }

    return textureID;
}

GLuint CelestialBody::GetTextureLoader(const char* path)
{
    return LoadTexture(path);
}