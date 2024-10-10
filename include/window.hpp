#pragma once

#include <gl/GL.h>
#include <GLFW/glfw3.h>

#include "camera_ext.hpp"

// settings
#define SCR_WIDTH 800
#define SCR_HEIGHT 600

// camera
extern Camera camera;
extern GLfloat lastX;
extern GLfloat lastY;
extern GLboolean firstMouse;

// timing
extern GLfloat deltaTime;	// time between current frame and last frame
extern GLfloat lastFrame;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
GLFWwindow* initWindow(int width, int height);
GLuint readTextureJPG(const char *);
GLuint readTexturePNG(const char *);