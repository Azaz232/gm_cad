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
	sun->InitAsSun();

	Planet* mercury = new Planet(0.4f, 15.0f, 5.0f, 60.0f, glm::vec3(0.6f, 0.6f, 0.6f), "textures/mercury.jpg");
	mercury->GenerateOrbit();
	bodies.push_back(mercury);

	Planet* venus = new Planet(0.9f, 12.0f, 8.0f, 40.0f, glm::vec3(0.85f, 0.85f, 0.6f), "textures/venus.png");
	venus->GenerateOrbit();
	bodies.push_back(venus);

	Planet* earth = new Planet(1.2f, 20.0f, 10.0f, 25.0f, glm::vec3(0.2f, 0.5f, 1.0f), "textures/earth.jpg");
	earth->GenerateOrbit();
	bodies.push_back(earth);

	Planet* mars = new Planet(0.6f, 22.0f, 16.0f, 18.0f, glm::vec3(0.9f, 0.3f, 0.2f), "textures/mars.jpg");
	mars->GenerateOrbit();
	bodies.push_back(mars);

	Planet* jupiter = new Planet(1.8f, 35.0f, 22.0f, 10.0f, glm::vec3(0.8f, 0.55f, 0.35f), "textures/jupiter.jpg");
	jupiter->GenerateOrbit();
	bodies.push_back(jupiter);

	Planet* saturn = new Planet(1.5f, 30.0f, 28.0f, 8.0f, glm::vec3(0.85f, 0.75f, 0.55f), "textures/saturn.jpg");
	saturn->GenerateOrbit();
	bodies.push_back(saturn);

	Planet* uranus = new Planet(1.1f, 25.0f, 34.0f, 6.0f, glm::vec3(0.5f, 0.8f, 0.8f), "textures/uranus.jpg");
	uranus->GenerateOrbit();
	bodies.push_back(uranus);

	Planet* neptune = new Planet(1.0f, 22.0f, 40.0f, 4.0f, glm::vec3(0.2f, 0.3f, 0.8f), "textures/neptune.jpg");
	neptune->GenerateOrbit();
	bodies.push_back(neptune);

	Planet* pluto = new Planet(0.3f, 10.0f, 45.0f, 2.0f, glm::vec3(0.7f, 0.65f, 0.6f), "textures/pluto.jpg");
	pluto->GenerateOrbit();
	bodies.push_back(pluto);

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
		planet->DrawOrbit();
		planet->Draw();
	}
}