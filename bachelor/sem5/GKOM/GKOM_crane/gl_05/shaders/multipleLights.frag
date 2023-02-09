#version 330 core
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;


out vec4 FragColor;



struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
  
uniform Material material;


uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir ){
	// perform perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5; 

	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;   

	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z; 

	 // check whether current frag pos is in shadow
	float bias = max(0.05 * (1.0 - dot(normal, -lightDir)), 0.005); 
	float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

	return shadow;
}



struct PointLight
{
	vec3 position;
	vec3 lightColor;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 6
uniform PointLight pointLights[NR_POINT_LIGHTS];


vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	//vec3 ambient  = light.ambient  * vec3(material.ambient);
    //vec3 diffuse  = light.diffuse  * diff * vec3(material.diffuse);
    //vec3 specular = light.specular * spec * vec3(material.specular);

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return light.lightColor*(ambient + diffuse + specular);
} 






struct DirLight {
	vec3 lightColor;

    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	//vec3 ambient  = light.ambient  * vec3(material.ambient);
    //vec3 diffuse  = light.diffuse  * diff * vec3(material.diffuse);
    //vec3 specular = light.specular * spec * vec3(material.specular);
	float shadow = ShadowCalculation(FragPosLightSpace, normal, light.direction);
    return light.lightColor*(ambient + (1.0f - shadow) * (diffuse + specular));
}  






uniform vec3 viewPos;
uniform float lightIntensity;


  
void main()
{

  // properties
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  // define an output color value
  vec3 output = vec3(0.0);

  // add the directional light's contribution to the output
  output += calcDirLight(dirLight, norm, viewDir);

  // do the same for all point lights
  for(int i = 0; i < NR_POINT_LIGHTS; i++)
	output += calcPointLight(pointLights[i], norm, FragPos, viewDir);

  // and add others lights as well (like spotlights)
  // output += someFunctionToCalculateSpotLight();
  
  FragColor = vec4(lightIntensity*output, 1.0);
} 