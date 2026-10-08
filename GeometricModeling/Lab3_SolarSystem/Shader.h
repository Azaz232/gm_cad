#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void Use();
	GLuint GetID() const { return id; }
private:
	GLuint id = 0;
};

