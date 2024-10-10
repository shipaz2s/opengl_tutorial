#include "shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::ifstream vertex_file, fragment_file;
	std::string vertex_str, fragment_str;
	
	try {
		vertex_file.open(vertexPath);
		std::stringstream vertex_stream;
		vertex_stream << vertex_file.rdbuf();
		vertex_file.close();
		vertex_str = vertex_stream.str();

		fragment_file.open(fragmentPath);
		std::stringstream fragment_stream;
		fragment_stream << fragment_file.rdbuf();
		fragment_file.close();
		fragment_str = fragment_stream.str();

	} catch (std::ifstream::failure ex) {
		std::cout << "ERROR reading shaders: " << ex.what() << std::endl;
	}

	const GLchar* vertex_code = vertex_str.c_str();
	const GLchar* fragment_code = fragment_str.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar info_log[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_code, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_code, NULL);
	glCompileShader(fragment);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(this->Program);
}