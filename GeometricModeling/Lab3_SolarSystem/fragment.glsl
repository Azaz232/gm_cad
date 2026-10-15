#version 330 core

out vec4 FragColor;

in vec3 FragPos; 
in vec3 Normal;  
in vec2 TexCoords; 

uniform vec3 objectColor; 
uniform sampler2D texture_diffuse;
uniform int hasTexture;

void main()
{
    if (objectColor.r > 1.1)
    {
        FragColor = vec4(1.0, objectColor.g, objectColor.b, 1.0);
        return;
    }
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
    vec3 norm = normalize(Normal);
    vec3 lightPos = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.02 * distance + 0.005 * (distance * distance));
    vec3 lightResult = ambient + (diffuse * attenuation);
    //vec4 texColor = texture(texture_diffuse, TexCoords);
    vec4 texColor = texture(texture_diffuse, vec2(TexCoords.x, 1.0 - TexCoords.y)); 
    vec3 finalColor = lightResult * texColor.rgb * objectColor;
    if (hasTexture == 1)
    {
        vec4 texColor = texture(texture_diffuse, vec2(TexCoords.x, 1.0 - TexCoords.y));
        finalColor = lightResult * texColor.rgb * objectColor;
    }
    else
    {
        finalColor = lightResult * objectColor;
    }
    FragColor = vec4(finalColor, 1.0);
}
