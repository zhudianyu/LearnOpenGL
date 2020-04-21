
#include <GL/glew.h>
#include "Shader.h"

using namespace std;
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{

	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);

	try
	{

		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "error shader file not successfully read" << endl;
	}
	const GLchar* vshaderCode = vertexCode.c_str();
	const GLchar* fshaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vshaderCode, NULL);
	glCompileShader(vertex);

	GLint sucess;
	GLchar infolog[512];
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		cout << "error vetex shader compile " << infolog << endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fshaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infolog);
		cout << "error frag shader compile " << infolog << endl;
	}

	Program = glCreateProgram();
	glAttachShader(Program, vertex);
	glAttachShader(Program, fragment);

	glLinkProgram(Program);
	glGetProgramiv(Program, GL_LINK_STATUS, &sucess);
	if (!sucess)
	{
		glGetProgramInfoLog(Program, 512, NULL, infolog);
		cout << "error program link failed" << infolog << endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(this->Program);
}


