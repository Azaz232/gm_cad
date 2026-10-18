#pragma once

#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "CelestialBody.h"
#include "Comet.h"

class Scene
{
public:
    Scene() = default;
    ~Scene();

    bool Init();

    void Update(float deltaTime);

    void Render(int windowWidth, int heightWindow);

    Camera& GetCamera() { return camera; }

    void SetMusyaOn(bool musyaOn) { MusyaOn = musyaOn; }
    bool GetMusyaOn() { return MusyaOn; }

private:
    Shader* spaceShader = nullptr;
    Camera camera;

    CelestialBody* sun = nullptr;
    Comet* activeComet = nullptr;
    std::vector<CelestialBody*> bodies;

    GLuint musyaVao = 0;
    GLuint musyaVbo = 0;
    GLuint musyaEbo = 0;

    bool MusyaOn = false;
    GLuint Musya;
};
