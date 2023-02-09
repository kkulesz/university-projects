#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

  
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;


out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);
    TexCoords = texCoord;

}