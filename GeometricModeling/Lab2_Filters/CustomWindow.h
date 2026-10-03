#pragma once

#include "Image.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class CustomWindow
{
public:
	CustomWindow() = default;
	~CustomWindow();

	bool Init();
	void Run();
private:
	Image originalImage;
	Image processedImage;

	bool imageIsLoaded = false;
	bool filterIsApplied = false;

	int selectedFilter = 0;

	void UpdateTexture(const Image& img, GLuint& textureId);
	//void DrawImage(GLuint textureId, int width, int height);

	GLFWwindow* window = nullptr;

	GLuint originalTexture = 0;
	GLuint processedTexture = 0;
};

