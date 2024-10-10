#pragma once
#include <GL/glew.h>
#include <GL/GL.h>

#include <glm/glm.hpp>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	void use();

	void setVec3(const char*, GLfloat, GLfloat, GLfloat);
	void setVec3(const char*, glm::vec3);
	void setFloat(const char*, GLfloat);
	void setInt(const char*, GLint);
	void setMat4(const char*, glm::mat4);
};