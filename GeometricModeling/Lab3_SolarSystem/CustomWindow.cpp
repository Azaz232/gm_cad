#include "CustomWindow.h"
#include <iostream>

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	CustomWindow* customWin = static_cast<CustomWindow*>(glfwGetWindowUserPointer(window));
	if (customWin)
	{
		customWin->ProcessMouseScroll(static_cast<float>(yoffset));
	}
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	CustomWindow* myWindow = static_cast<CustomWindow*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double currentTime = glfwGetTime();
		
		if (currentTime - myWindow->m_time <= 0.4)
		{
			myWindow->scene.SetMusyaOn(!myWindow->scene.GetMusyaOn());
		}
		
		myWindow->m_time = currentTime;
	}
}

CustomWindow::~CustomWindow()
{
	if (!window)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

bool CustomWindow::Init()
{
	if (!glfwInit())
	{
		return false;
	}
	
	window = glfwCreateWindow(1200, 600, "3d solar system", nullptr, nullptr);
	
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	if (!scene.Init())
	{
		return false;
	}

	glfwSetWindowUserPointer(window, this);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	return true;
}

void CustomWindow::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.Update(deltaTime);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);

		scene.Render(width, height);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void CustomWindow::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) scene.GetCamera().ProcessKeyboard(1, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) scene.GetCamera().ProcessKeyboard(2, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) scene.GetCamera().ProcessKeyboard(3, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) scene.GetCamera().ProcessKeyboard(4, deltaTime);
}

void CustomWindow::ProcessMouseScroll(float yOffset)
{
	scene.GetCamera().ProcessMouse(yOffset);
}
