#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "learnopengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glewExperimental = GL_TRUE;
	GLfloat vertices[] = {
	0.5,-0.5,0, 1,0,0,
	-0.5,-0.5,0, 0,1,0,
	0,0.5,0, 0,0,1
	};
	glViewport(0, 0, 800, 600);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initalize glew" << std::endl;
		return -1;
	}


 	Shader ourShader("../Shader/default.vs", "../Shader/default.frag");
 
 
 	GLuint VBO, VAO;
 	glGenVertexArrays(1, &VAO);
 	glGenBuffers(1, &VBO);
 	glBindVertexArray(VAO);
 
 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
 	glEnableVertexAttribArray(0);
 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GLfloat)));
 	glEnableVertexAttribArray(1);
 	//½â°óvao
 	glBindVertexArray(0);
 
 	while (!glfwWindowShouldClose(window))
 	{
 		glfwPollEvents();
 
 		glClearColor(0.2, 0.3, 0.3, 1);
 		glClear(GL_COLOR_BUFFER_BIT);
 
		GLint vertexOffsetLocation = glGetUniformLocation(ourShader.Program, "offset");

 		ourShader.Use();
		glUniform2f(vertexOffsetLocation, 0.5f, 0);
 		glBindVertexArray(VAO);
 		glDrawArrays(GL_TRIANGLES, 0, 3);
 		glBindVertexArray(0);
 
 		glfwSwapBuffers(window);
 	}
 	glDeleteVertexArrays(1, &VAO);
 	glDeleteBuffers(1, &VBO);
 	glfwTerminate();

	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}