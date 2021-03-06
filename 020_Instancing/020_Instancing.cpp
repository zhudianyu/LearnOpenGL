// #define GLEW_STATIC
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <SOIL.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include "common/Shader.h"
// #include "common/Camera.h"
// #include <map>
// #include "common/Model.h"
// using namespace std;
// // Window dimensions
// const GLuint WIDTH = 800, HEIGHT = 600;
// // Camera
// Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
// GLfloat lastX = WIDTH / 2.0;
// GLfloat lastY = HEIGHT / 2.0;
// bool    keys[1024];
// 
// // Deltatime
// GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
// GLfloat lastFrame = 0.0f;  	// Time of last frame
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// void do_movement();
// 
// const string projName = "020_Instancing";
// GLuint GenTexture(const char* path)
// {
// 	int width, height;
// 	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
// 	GLuint textureID;
// 	glGenTextures(1, &textureID);
// 	glActiveTexture(GL_TEXTURE0);
// 
// 	glBindTexture(GL_TEXTURE_2D, textureID);
// 	//纹理环绕
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	//纹理放大缩小
// // 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// // 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	//多级渐进纹理采样 纹理放大不会使用多级渐远纹理
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 	glGenerateMipmap(GL_TEXTURE_2D);
// 	SOIL_free_image_data(image);
// 	glBindTexture(GL_TEXTURE_2D, 0);
// 	return textureID;
// }
// GLuint GenAlphaTexture(const char* path)
// {
// 	int width, height;
// 	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
// 	GLuint textureID;
// 	glGenTextures(1, &textureID);
// 	glActiveTexture(GL_TEXTURE0);
// 
// 	glBindTexture(GL_TEXTURE_2D, textureID);
// 	//纹理环绕
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	//纹理放大缩小
// // 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// // 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	//多级渐进纹理采样 纹理放大不会使用多级渐远纹理
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 	glGenerateMipmap(GL_TEXTURE_2D);
// 	SOIL_free_image_data(image);
// 	glBindTexture(GL_TEXTURE_2D, 0);
// 	return textureID;
// }
// GLFWwindow* InitGL()
// {
// 	glfwInit();
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
// 	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, projName.c_str(), nullptr, nullptr);
// 	glfwMakeContextCurrent(window);
// 	glfwSetKeyCallback(window, key_callback);
// 	glfwSetCursorPosCallback(window, mouse_callback);
// 	glfwSetScrollCallback(window, scroll_callback);
// 	// GLFW Options
// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
// 	glewExperimental = GL_TRUE;
// 
// 	glViewport(0, 0, 800, 600);
// 
// 	if (glewInit() != GLEW_OK)
// 	{
// 		std::cout << "failed to initalize glew" << std::endl;
// 		return NULL;
// 	}
// 	return window;
// }
// //int main()
// int drawQuad()
// {
// 	GLFWwindow* window = InitGL();
// 
// 	float quadVertices[] = {
// 		// 位置          // 颜色
// 		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
// 		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
// 		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
// 
// 		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
// 		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
// 		 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
// 	};
// 
// 
// 
// 	//020_Instancing
// 
// 	//Shader quadShader("../020_Instancing/quad.vert", "../020_Instancing/quad.frag");
// 	Shader quadArrayShader("../020_Instancing/quadarray.vert", "../020_Instancing/quad.frag");
// 
// 	glm::vec2 translations[100];
// 	int index = 0;
// 	float offset = 0.1f;
// 	for (int y = -10; y < 10; y += 2)
// 	{
// 		for (int x = -10; x < 10; x += 2)
// 		{
// 			glm::vec2 temp;
// 			temp.x = (float)x / 10.0f + offset;
// 			temp.y = (float)y / 10.0f + offset;
// 			translations[index++] = temp;
// 		}
// 	}
// 	GLuint pVAO, pVBO;
// 	glGenVertexArrays(1, &pVAO);
// 	glBindVertexArray(pVAO);
// 
// 	glGenBuffers(1, &pVBO);
// 	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
// 
// 
// 	unsigned int  instanceVBO;
// 	glGenBuffers(1, &instanceVBO);
// 
// 	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(2 * sizeof(GLfloat)));
// 	glEnableVertexAttribArray(1);
// 
// 	glEnableVertexAttribArray(2);
// 	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
// 
// 	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
// 	glBindBuffer(GL_ARRAY_BUFFER, 0);
// 	glVertexAttribDivisor(2, 1);
// 
// 	glBindVertexArray(0);
// 
// // 	quadShader.Use();
// // 	for (int i = 0; i < 100; i++)
// // 	{
// // 		stringstream ss;
// // 		string index;
// // 		ss << i;
// // 		index = ss.str();
// // 		//uniform 上限 1024 
// // 		quadShader.setVec2(("offsets[" + index + "]").c_str(), translations[i]);
// // 	}
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		GLfloat currentFrame = glfwGetTime();
// 		deltaTime = currentFrame - lastFrame;
// 		lastFrame = currentFrame;
// 		glfwPollEvents();
// 		do_movement();
// 		//first pass
// 		glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 		glEnable(GL_DEPTH_TEST);
// 		glClearColor(0.2, 0.3, 0.3, 1);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 
// 
// 		glm::mat4 view(1.0f);
// 		view = camera.GetViewMatrix();
// 		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
// 		quadArrayShader.Use();
// 
// 		glBindVertexArray(pVAO);
// 		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
// 		glBindVertexArray(0);
// 
// 		glfwSwapBuffers(window);
// 	}
// 
// 	//glDeleteFramebuffers(1, &fbo);
// 	glfwTerminate();
// 	return 0;
// }
// #pragma region camera
// 
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
// {
// 	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
// 		glfwSetWindowShouldClose(window, GL_TRUE);
// 	if (key >= 0 && key < 1024)
// 	{
// 		if (action == GLFW_PRESS)
// 			keys[key] = true;
// 		else if (action == GLFW_RELEASE)
// 			keys[key] = false;
// 	}
// }
// 
// void do_movement()
// {
// 	// Camera controls
// 	if (keys[GLFW_KEY_S])
// 		camera.ProcessKeyboard(FORWARD, deltaTime);
// 	if (keys[GLFW_KEY_W])
// 		camera.ProcessKeyboard(BACKWARD, deltaTime);
// 	if (keys[GLFW_KEY_D])
// 		camera.ProcessKeyboard(LEFT, deltaTime);
// 	if (keys[GLFW_KEY_A])
// 		camera.ProcessKeyboard(RIGHT, deltaTime);
// }
// float mouseMoveFactor = 0.1f;
// bool firstMouse = true;
// void mouse_callback(GLFWwindow* window, double xpos, double ypos)
// {
// 	if (firstMouse)
// 	{
// 		lastX = xpos;
// 		lastY = ypos;
// 		firstMouse = false;
// 	}
// 
// 	GLfloat xoffset = xpos - lastX;
// 	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
// 
// 	lastX = xpos;
// 	lastY = ypos;
// 
// 	camera.ProcessMouseMovement(xoffset * mouseMoveFactor, yoffset * mouseMoveFactor);
// }
// 
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
// 	camera.ProcessMouseScroll(yoffset * mouseMoveFactor);
// }
// #pragma endregion camera