#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include <map>
using namespace std;
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

const string projName = "017_CubeMap";
GLuint GenTexture(const char* path)
{
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureID);
	//������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����Ŵ���С
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//�༶����������� ����Ŵ󲻻�ʹ�ö༶��Զ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}
GLuint GenAlphaTexture(const char* path)
{
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureID);
	//������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//����Ŵ���С
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//�༶����������� ����Ŵ󲻻�ʹ�ö༶��Զ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}
GLFWwindow* InitGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, projName.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glewExperimental = GL_TRUE;

	glViewport(0, 0, 800, 600);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initalize glew" << std::endl;
		return NULL;
	}
	return window;
}
int main()
{
	GLFWwindow* window = InitGL();
#pragma region data
	float cubeMapvertices[] = {
		// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
	};
	float vertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
	};

	GLfloat texCoords[] = {
		0,0,//����
		1,0,//����
		0.5f,1.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  -3.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};
#pragma endregion data
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//�������Ե����� ��Ӧ������ɫ����λ�� layout location = 2 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//���vao
	glBindVertexArray(0);


	GLuint cubeMapVBO, cubeMapVAO;
	glGenVertexArrays(1, &cubeMapVAO);
	glBindVertexArray(cubeMapVAO);

	glGenBuffers(1, &cubeMapVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeMapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMapvertices), cubeMapvertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//���vao
	glBindVertexArray(0);
	Shader ourShader("../017_CubeMap/default.vs", "../017_CubeMap/default.frag");
	Shader screenShader("../017_CubeMap/quad.vs", "../017_CubeMap/quad.frag");
	Shader cubemapShader("../017_CubeMap/cubemap.vs", "../017_CubeMap/cubemap.frag");
	cubemapShader.Use();
	cubemapShader.setInt("ourTexture", 0);

	GLuint textureID = GenTexture("../Resources/img/wall.jpg");
	GLuint faceTextureID = GenTexture("../Resources/img/awesomeface.png");

	//��Ȳ���
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
#pragma region cubemaptexture
	unsigned int cubeTextureID;
	glGenTextures(1, &cubeTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);
	int imageWidth, imageHeight,nrChannels;
	vector<std::string> faces
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};
	
	for (int i = 0; i < faces.size(); i++)
	{
		string path("../Resources/img/skybox/");
		path = path + faces[i];
		unsigned char* image = SOIL_load_image(path.c_str(), &imageWidth, &imageHeight, &nrChannels, 0);
		if (image)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SOIL_free_image_data(image);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
#pragma endregion cubemaptexture

#pragma region fbo
	//fbo ����֡�������
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//��������
	GLuint textureColorBuffer;
	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	//���һ��������ʾ���������� �����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*
	target��������������֡�������͵�Ŀ�꣨���ơ���ȡ�����߶��У���
	attachment�����������ӵĸ��������͡��������Ǹ��ӵ���һ����ɫ��������Ҫע�⣬�����Ǹ�0�ǰ�ʾ���ǿ��Ը���1��������ɫ�ĸ��������ǻ��ں���Ľ̳���̸����
	textarget����ϣ�����ӵ��������͡�
	texture�����ӵ�ʵ������
	level��Mipmap level����������Ϊ0��
	*/
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);


	//������Ⱦ������� һ������Ⱥ�ģ�� ������
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);

	//����Ⱦ������󸽼ӵ�֡�������Ⱥ�ģ�帽����
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{//�󶨵�Ĭ�ϻ���
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
#pragma region ƽ��
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//�������Ե����� ��Ӧ������ɫ����λ�� layout location = 2 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//���vao
	glBindVertexArray(0);
#pragma endregion ƽ��
	ourShader.Use();

	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

	screenShader.Use();
	glUniform1i(glGetUniformLocation(screenShader.Program, "screenTexture"), 0);
#pragma endregion fbo
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		do_movement();
		//first pass
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);


#pragma region cube
		ourShader.Use();
		view = camera.GetViewMatrix();
		ourShader.setMat("view",view);
		ourShader.setMat("projection",projection);
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 0;
			if (i % 3 == 0)
			{
				angle = (GLfloat)glfwGetTime() * 20.0f;
			}
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1, 0.3f, 0.5f));
			ourShader.setMat("model", model);
			/*glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));*/
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
#pragma endregion cube
#pragma region renfbo
		//second pass֡����
// 		glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 		glDisable(GL_DEPTH_TEST);
// 		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT);
// 
// 
// 		screenShader.Use();
// 
// 		glBindVertexArray(quadVAO);
// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
// 		glDrawArrays(GL_TRIANGLES, 0, 6);
// 		glBindVertexArray(0);
#pragma endregion renfbo
		//��պзŵ������Ⱦ ����ƬԪ��ɫ���ĵ��� �ı��������ֵΪ���ֵ
#pragma region skybox 
	//	glDepthMask(GL_FALSE);
		cubemapShader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		ourShader.setMat("view", view);
		ourShader.setMat("projection", projection);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);
		glBindVertexArray(cubeMapVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		//glDepthMask(GL_TRUE);
#pragma endregion

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteFramebuffers(1, &fbo);
	glfwTerminate();
	return 0;
}
#pragma region camera

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
float mouseMoveFactor = 0.1f;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset * mouseMoveFactor, yoffset * mouseMoveFactor);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset * mouseMoveFactor);
}
#pragma endregion camera