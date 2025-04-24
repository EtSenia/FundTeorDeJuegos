#pragma once
#include <GL/glew.h>
#include <string>
#include "GLSProgram.h"

class Sprite
{
	float x, y;
	int width, height;
	GLuint vboID;
	GLuint shaderProgram;
	GLSProgram shaders;

	GLuint compileShader(GLenum type, const char* source);
	void createShader(const std::string& vertexFile, const std::string& fragmentFile);
public:
	Sprite();
	~Sprite();
	void init(float x, float y, int width, int height);
	void draw();
};

