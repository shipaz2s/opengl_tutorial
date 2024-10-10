#pragma once
#include <GL/glew.h>
#include <GL/GL.h>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	void use();
};