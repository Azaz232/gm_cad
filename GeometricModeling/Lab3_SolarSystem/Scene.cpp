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
	if (musyaVao != 0) glDeleteVertexArrays(1, &musyaVao);

	if (spaceShader) delete spaceShader;
}

bool Scene::Init()
{
	spaceShader = new Shader("vertex.glsl", "fragment.glsl");
	sun = new CelestialBody(3.5f, 10.0f);
	sun->InitAsSun();

	Musya = sun->GetTextureLoader("textures/musya1.png");

	Planet* mercury = new Planet(0.25f, 15.0f, 6.0f, 60.0f, glm::vec3(0.6f, 0.6f, 0.6f), "textures/mercury.jpg");
	mercury->GenerateOrbit();
	bodies.push_back(mercury);

	Planet* venus = new Planet(0.45f, 12.0f, 9.0f, 40.0f, glm::vec3(0.85f, 0.85f, 0.6f), "textures/venus.png");
	venus->GenerateOrbit();
	bodies.push_back(venus);

	Planet* earth = new Planet(0.5f, 20.0f, 12.0f, 25.0f, glm::vec3(0.2f, 0.5f, 1.0f), "textures/earth.jpg");
	earth->GenerateOrbit();
	bodies.push_back(earth);

	Planet* mars = new Planet(0.35f, 22.0f, 15.0f, 18.0f, glm::vec3(0.9f, 0.3f, 0.2f), "textures/mars.jpg");
	mars->GenerateOrbit();
	bodies.push_back(mars);

	Planet* jupiter = new Planet(1.3f, 35.0f, 20.0f, 10.0f, glm::vec3(0.8f, 0.55f, 0.35f), "textures/jupiter.jpg");
	jupiter->GenerateOrbit();
	bodies.push_back(jupiter);

	Planet* saturn = new Planet(1.1f, 30.0f, 25.0f, 8.0f, glm::vec3(0.85f, 0.75f, 0.55f), "textures/saturn.jpg");
	saturn->GenerateOrbit();
	bodies.push_back(saturn);

	Planet* uranus = new Planet(0.8f, 25.0f, 31.0f, 6.0f, glm::vec3(0.5f, 0.8f, 0.8f), "textures/uranus.jpg");
	uranus->GenerateOrbit();
	bodies.push_back(uranus);

	Planet* neptune = new Planet(0.75f, 22.0f, 37.0f, 4.0f, glm::vec3(0.2f, 0.3f, 0.8f), "textures/neptune.jpg");
	neptune->GenerateOrbit();
	bodies.push_back(neptune);

	Planet* pluto = new Planet(0.15f, 10.0f, 43.0f, 2.0f, glm::vec3(0.7f, 0.65f, 0.6f), "textures/pluto.jpg");
	pluto->GenerateOrbit();
	bodies.push_back(pluto);

	Comet* myComet = new Comet(0.4f, 50.0f, 25.0f, 8.0f, 35.0f);
	bodies.push_back(myComet);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	GLint currentProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	glm::vec3 foundCometPos = glm::vec3(0.0f);
	bool cometExists = false;

	for (auto* body : bodies)
	{
		if (Comet* c = dynamic_cast<Comet*>(body))
		{
			foundCometPos = c->GetPosition();
			cometExists = true;
			break;
		}
	}

	if (cometExists)
	{
		glUniform3f(glGetUniformLocation(currentProgram, "cometPos"), foundCometPos.x, foundCometPos.y, foundCometPos.z);
		glUniform1i(glGetUniformLocation(currentProgram, "isCometActive"), 1);
	}
	else
	{
		glUniform1i(glGetUniformLocation(currentProgram, "isCometActive"), 0);
	}

	if (sun)
	{
		if (MusyaOn)
		{
			sun->SetTextureOverride(Musya);
		}
		else
		{
			sun->ClearTextureOverride();
		}

		sun->Draw(); 
	}

	for (auto* body : bodies)
	{
		body->DrawOrbit(); 
		body->Draw();      
	}
}
