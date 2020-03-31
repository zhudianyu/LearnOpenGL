#define  GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{//glinti函数要调用
	GLuint vetex;
	vetex = glCreateShader(GL_VERTEX_SHADER);
	int a = 0;
	std::cout << a << std::endl;
	return 0;
}