#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

class CustomWindow
{
public:
    CustomWindow() = default;
    ~CustomWindow(); 

    bool Init();     
    void Run();
private:
    void ProcessInput(); 

    GLFWwindow* window = nullptr;
    Scene scene; 

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};
