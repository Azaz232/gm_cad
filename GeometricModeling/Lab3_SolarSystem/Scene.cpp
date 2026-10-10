#include "Scene.h"
#include "Planet.h"
#include "Comet.h"
#include <glm/gtc/type_ptr.hpp>

Scene::~Scene()
{
	if (sun) delete sun;

	for (auto* body : bodies)
	{
		delete body;
	}

	if (spaceShader) delete spaceShader;
}

bool Scene::Init()
{
	spaceShader = new Shader("vertex.glsl", "fragment.glsl");
	sun = new CelestialBody(3.0f, 10.0f);

	Planet* earth = new Planet(1.2f, 20.0f, 10.0f, 25.0f);
	bodies.push_back(earth);

	Comet* myComet = new Comet(0.4f, 50.0f, 18.0f, 5.0f, 35.0f);
	bodies.push_back(myComet);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Scene::Update(float deltaTime)
{
	sun->Update(deltaTime);
	for (auto* planet : bodies)
	{
		planet->Update(deltaTime);
	}
}

void Scene::Render(int windowWidth, int windowHeight)
{
	if (!spaceShader) return;

	spaceShader->Use();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();

	glUniformMatrix4fv(glGetUniformLocation(spaceShader->GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(spaceShader->GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	sun->Draw();
	for (auto* planet : bodies)
	{
		planet->Draw();
	}
}