#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D diffuse;
uniform float lightIntensity;
uniform vec3 lightColor;


void main()
{
	vec3 textured = vec3(texture(diffuse, TexCoords));
	//color = vec4(lightColor*lightIntensity*textured, 1.0f);	
	color = vec4(lightIntensity*textured, 1.0f);	
}
