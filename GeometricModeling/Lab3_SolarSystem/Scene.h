#pragma once

#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "CelestialBody.h"

class Scene
{
public:
    Scene() = default;
    ~Scene();

    bool Init();

    void Update(float deltaTime);

    void Render(int windowWidth, int heightWindow);

    Camera& GetCamera() { return camera; }

private:
    Shader* spaceShader = nullptr;
    Camera camera;

    CelestialBody* sun = nullptr;
    std::vector<CelestialBody*> bodies;
};
