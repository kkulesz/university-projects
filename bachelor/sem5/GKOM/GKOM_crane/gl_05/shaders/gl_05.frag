#version 330 core
in vec3 vecColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
	// ambient
	float ambientStrength = 0.3f;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec4 textured = mix(texture(Texture0, TexCoord), texture(Texture1, TexCoord), 0.4);
	vec3 result = vec3(textured.x, textured.y, textured.z) * (ambient + diffuse + specular);
    color = vec4(result, 1.0f);
}
