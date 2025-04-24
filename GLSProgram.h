#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class GLSProgram
{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint vertexShaderID;

	void compileShader(const std::string& shaderPath, GLuint id);
	void compileShaderOrFallback(const std::string& shaderFilePath,
		GLuint shaderID,
		const char* fallbackSource);
	void linkShader();

public:
	GLSProgram();
	~GLSProgram();
	int numAtribute;
	void addAtribute(const string atributeName);
	void use();
	void unuse();
	void compileShaders(const std::string& vertexShaderFilePath,
		const string& fragmentShaderFilePath);


};