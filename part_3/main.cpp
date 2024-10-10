#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.hpp"
#include "camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

GLfloat visibility = 0.4;

float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

float deltaTime = 0.05f;
float lastFrame = 0.0f;

glm::mat4 view = glm::mat4(1.0f);

float speed = 0.2f;
glm::vec3 left_vec = glm::vec3(-1.0f, 0.0f, 0.0f);
glm::vec3 up_vec = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 forward_vec = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 pos_vec = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 center_vec = glm::vec3(0.0f, 0.0f, 0.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if ( key == GLFW_KEY_UP) {
		up_vec = glm::rotate(up_vec, glm::radians(5.0f), pos_vec);
		view = glm::lookAt(pos_vec, center_vec, up_vec);
		// view = glm::rotate(view, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	} else if ( key == GLFW_KEY_DOWN) {
		up_vec = glm::rotate(up_vec, -glm::radians(5.0f), pos_vec);
		view = glm::lookAt(pos_vec, center_vec, up_vec);
		// view = glm::rotate(view, glm::radians(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	} else if ( key == GLFW_KEY_LEFT ) {
		auto vec = glm::rotate(center_vec - pos_vec, glm::radians(5.0f), up_vec);
		center_vec = pos_vec + vec;
		left_vec = glm::normalize( glm::cross(pos_vec - center_vec, up_vec) );
		forward_vec = glm::normalize( glm::cross(left_vec, up_vec) );

		view = glm::lookAt(pos_vec, center_vec, up_vec);
		
		if (action == GLFW_PRESS || action == GLFW_RELEASE) {
			std::cout << "-----LEFT-----" << std::endl;
			std::cout << "pos ("<<  pos_vec.x << ", " << pos_vec.y << ", " << pos_vec.z << ")" << std::endl;
			std::cout << "center ("<<  center_vec.x << ", " << center_vec.y << ", " << center_vec.z << ")" << std::endl;
			std::cout << "left_vec ("<<  left_vec.x << ", " << left_vec.y << ", " << left_vec.z << ")" << std::endl;
			std::cout << "up_vec ("<<  up_vec.x << ", " << up_vec.y << ", " << up_vec.z << ")" << std::endl;
			std::cout << "speed " << speed << std::endl;
		}

	} else if ( key == GLFW_KEY_RIGHT ) {

		auto vec = glm::rotate(center_vec - pos_vec, -glm::radians(5.0f), up_vec);
		center_vec = pos_vec + vec;
		left_vec = glm::normalize( glm::cross(pos_vec - center_vec, up_vec) );
		forward_vec = glm::normalize( glm::cross(left_vec, up_vec) );

		view = glm::lookAt(pos_vec, center_vec, up_vec);

		if (action == GLFW_PRESS || action == GLFW_RELEASE) {
			std::cout << "-----RIGHT-----" << std::endl;
			std::cout << "pos ("<<  pos_vec.x << ", " << pos_vec.y << ", " << pos_vec.z << ")" << std::endl;
			std::cout << "center ("<<  center_vec.x << ", " << center_vec.y << ", " << center_vec.z << ")" << std::endl;
			std::cout << "left_vec ("<<  left_vec.x << ", " << left_vec.y << ", " << left_vec.z << ")" << std::endl;
			std::cout << "up_vec ("<<  up_vec.x << ", " << up_vec.y << ", " << up_vec.z << ")" << std::endl;
			std::cout << "speed " << speed << std::endl;
		}		
	} else if ( key == GLFW_KEY_W ) {
		pos_vec += speed * forward_vec;
		view = glm::lookAt(pos_vec, center_vec, up_vec);
	} else if ( key == GLFW_KEY_S ) {
		pos_vec -= speed * forward_vec;
		view = glm::lookAt(pos_vec, center_vec, up_vec);
	} else if ( key == GLFW_KEY_A ) {
		center_vec += speed * left_vec;
		pos_vec += speed * left_vec;
		view = glm::lookAt(pos_vec, center_vec, up_vec);

		if (action == GLFW_PRESS || action == GLFW_RELEASE) {
			std::cout << "-----MOVE LEFT-----" << std::endl;
			std::cout << "pos ("<<  pos_vec.x << ", " << pos_vec.y << ", " << pos_vec.z << ")" << std::endl;
			std::cout << "center ("<<  center_vec.x << ", " << center_vec.y << ", " << center_vec.z << ")" << std::endl;
			std::cout << "left_vec ("<<  left_vec.x << ", " << left_vec.y << ", " << left_vec.z << ")" << std::endl;
			std::cout << "up_vec ("<<  up_vec.x << ", " << up_vec.y << ", " << up_vec.z << ")" << std::endl;
			std::cout << "speed " << speed << std::endl;
		}
	} else if ( key == GLFW_KEY_D ) {
		center_vec -= speed * left_vec;
		pos_vec -= speed * left_vec;
		view = glm::lookAt(pos_vec, center_vec, up_vec);

		if (action == GLFW_PRESS || action == GLFW_RELEASE) {
			std::cout << "-----MOVE RIGHT-----" << std::endl;
			std::cout << "pos ("<<  pos_vec.x << ", " << pos_vec.y << ", " << pos_vec.z << ")" << std::endl;
			std::cout << "center ("<<  center_vec.x << ", " << center_vec.y << ", " << center_vec.z << ")" << std::endl;
			std::cout << "left_vec ("<<  left_vec.x << ", " << left_vec.y << ", " << left_vec.z << ")" << std::endl;
			std::cout << "up_vec ("<<  up_vec.x << ", " << up_vec.y << ", " << up_vec.z << ")" << std::endl;
			std::cout << "speed " << speed << std::endl;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    // lastX = xpos;
    // lastY = ypos;

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

int main()
{
	std::cout << "pos ("<<  pos_vec.x << ", " << pos_vec.y << ", " << pos_vec.z << ")" << std::endl;
	std::cout << "center ("<<  center_vec.x << ", " << center_vec.y << ", " << center_vec.z << ")" << std::endl;
	std::cout << "left_vec ("<<  left_vec.x << ", " << left_vec.y << ", " << left_vec.z << ")" << std::endl;
	std::cout << "up_vec ("<<  up_vec.x << ", " << up_vec.y << ", " << up_vec.z << ")" << std::endl;
	std::cout << "speed " << speed << std::endl;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Part3", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return - 1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0,0, width, height);
	glfwSetKeyCallback(window, key_callback);

	//-----------------------------------------------------------------------------------------------------------
	Shader shader("part_3/triangle.vs", "part_3/triangle.fs");

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //red
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, //green
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //blue
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //white
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	
	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
	
	// GLuint indices[] = {
	// 	0, 1, 3,
	// 	1, 2, 3
	// };

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// GLuint EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int texture_width, texture_height, texture_nrChannels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* texture_data = stbi_load("resources/textures/container.jpg", &texture_width, &texture_height, &texture_nrChannels, 0);

	if (texture_data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture file" << std::endl;
	}
	stbi_image_free(texture_data);


	
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture_data = stbi_load("resources/textures/awesomeface.png", &texture_width, &texture_height, &texture_nrChannels, 0);

	if (texture_data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture file" << std::endl;
	}
	stbi_image_free(texture_data);

	shader.use();
	glUniform1i(glGetUniformLocation(shader.Program, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "texture2"), 1);

	// glm::mat4 model = glm::mat4(1.0f);
	// model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.5f, 1.0f, 0.0f));
	// glm::mat4 view = glm::mat4(1.0f);
	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	view = glm::lookAt(pos_vec, center_vec, up_vec);
	// glm::mat4 view;
	const float radius = 10.0f;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST); 

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindVertexArray(VAO);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		for (int i = 0; i < 1; ++i) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			// model = glm::rotate(model, 20.f * i, glm::vec3(0.5f, 1.0f, 0.0f));
			// model = glm::rotate(model, static_cast<float>( glfwGetTime() + 10*i ) * static_cast<float>( pow(-1.0, i) ), glm::vec3(0.5f, 1.0f, 0.0f));

			glUniform1f(glGetUniformLocation(shader.Program, "visibility"), visibility);

			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();

	return 0;
}