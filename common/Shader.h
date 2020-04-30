#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = NULL);
	Shader(std::string vertexPath, std::string fragmentPath);
	void Create(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = NULL);
	// uniform¹¤¾ßº¯Êý
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat(const std::string& name, glm::mat4 value);
	void setMat4(const std::string& name, glm::mat4 value);
	void setVec3(const std::string& name, glm::vec3 vaue);
	void setVec2(const std::string& name, glm::vec2 vaue);
	void Use();
};

#endif // !