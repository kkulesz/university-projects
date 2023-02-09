#pragma once

#include <GL/glew.h>
#include <memory>
#include "shader.h"

class Texture
{
public:
	Texture(std::string fname);
	void use(Shader& shader, int textureUnit);
	//const char* getFname();
	


private:
	std::string fname;
	GLuint texture;
	GLuint LoadMipmapTexture(GLuint texId, std::string fname);
	
};