#version 330 core

out vec4 FragColor;

in vec3 FragPos; 
in vec3 Normal;  

uniform vec3 objectColor; 

void main()
{
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
    vec3 norm = normalize(Normal);
    vec3 lightPos = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    vec3 lightResult = (ambient + diffuse) * objectColor;
    if (objectColor.r > 1.1)
    {
        FragColor = vec4(1.0, objectColor.g, objectColor.b, 1.0);
    }
    else
    {
        FragColor = vec4(lightResult, 1.0);
    }
}
