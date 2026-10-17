#version 330 core

out vec4 FragColor;

in vec3 FragPos; 
in vec3 Normal;  
in vec2 TexCoords; 

uniform vec3 objectColor; 
uniform sampler2D texture_diffuse; 
uniform int hasTexture; 

uniform vec3 cometPos;
uniform int isCometActive; 

void main()
{
    if (objectColor.r > 1.1)
    {
       // if (hasTexture == 1) {
         //   vec4 sunTex = texture(texture_diffuse, vec2(TexCoords.x, 1.0 - TexCoords.y));
         //   FragColor = vec4(sunTex.rgb, 1.0);
        //} else {
        //    FragColor = vec4(1.0, objectColor.g, objectColor.b, 1.0);
        //}
        //return;
        vec4 sunTex = texture(texture_diffuse, vec2(TexCoords.x, 1.0 - TexCoords.y));
        FragColor = sunTex; 
        return;
    }
    if (objectColor.g > 1.1)
    {
        FragColor = vec4(objectColor.r, 1.0, objectColor.b, 1.0); 
        return;
    }
    vec3 norm = normalize(Normal);
    float ambientStrength = 0.35;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
    vec3 sunPos = vec3(0.0, 0.0, 0.0);
    vec3 sunLightDir = normalize(sunPos - FragPos);
    float sunDiff = max(dot(norm, sunLightDir), 0.0);
    float sunDist = length(sunPos - FragPos);
    float sunAttenuation = 1.0 / (1.0 + 0.02 * sunDist + 0.005 * (sunDist * sunDist));
    vec3 sunDiffuse = sunDiff * vec3(1.0, 1.0, 1.0) * sunAttenuation;
    vec3 cometDiffuse = vec3(0.0);
    if (isCometActive == 1)
    {
        vec3 cometLightDir = normalize(cometPos - FragPos);
        float cometDiff = max(dot(norm, cometLightDir), 0.0);
        float cometDist = length(cometPos - FragPos);
        float cometAttenuation = 1.0 / (1.0 + 0.1 * cometDist + 0.08 * (cometDist * cometDist));
        cometDiffuse = cometDiff * vec3(0.4, 0.9, 0.4) * cometAttenuation;
    }
    vec3 totalLight = ambient + sunDiffuse + cometDiffuse;
    vec3 finalColor;
    if (hasTexture == 1)
    {
        vec4 texColor = texture(texture_diffuse, vec2(TexCoords.x, 1.0 - TexCoords.y));
        finalColor = totalLight * texColor.rgb * objectColor;
    }
    else
    {
        finalColor = totalLight * objectColor;
    }
    FragColor = vec4(finalColor, 1.0);
}
