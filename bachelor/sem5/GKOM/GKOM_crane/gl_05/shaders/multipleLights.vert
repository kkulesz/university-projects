#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;


  
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);
    TexCoords = texCoord;

	FragPos = vec3(transform * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(transform))) * normal;

	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);
} 