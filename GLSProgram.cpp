#include "GLSProgram.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "Error.h"
#include <string>

using namespace std;

GLSProgram::GLSProgram() : programID(0), vertexShaderID(0),
fragmentShaderID(0), numAtribute(0){}

void GLSProgram::linkShader() {
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(programID);
		//Don't leak shaders either.
		fatalError("Shaders do not linked "
			+ printf("%s", &(infoLog[0])));

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}


void GLSProgram::compileShaders(const std::string& vertexShaderFilePath,
	const std::string& fragmentShaderFilePath) {
	std::string vertexSrc, fragmentSrc;

	const char* fallbackVertex = R"(
        #version 330 core
        layout(location = 0) in vec2 position;
        layout(location = 1) in vec4 vertexColor;

        out vec4 fragColor;

        void main() {
            gl_Position = vec4(position, 0.0, 1.0);
            fragColor = vertexColor;
        })";

	const char* fallbackFragment = R"(
        #version 330 core
        in vec4 fragColor;
        out vec4 color;

        void main() {
            color = fragColor;
        })";

	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {

	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {

	}

	compileShaderOrFallback(vertexShaderFilePath, vertexShaderID, fallbackVertex);
	compileShaderOrFallback(fragmentShaderFilePath, fragmentShaderID, fallbackFragment);

	linkShader();
}
void GLSProgram::compileShaderOrFallback(const std::string& shaderFilePath, GLuint shaderID, const char* fallbackSource)
{
	if (shaderFilePath.empty()) {
		std::cout << "No se especific un archivo para el shader. Usando fallback.\n";
		compileShader(fallbackSource, shaderID);
	}
	else {
		compileShader(shaderFilePath, shaderID);
	}
}
void GLSProgram::compileShader(const std::string& shaderPath, GLuint id) {

	string filecontent = "";
	string line = "";

	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("Could not open " + shaderPath);
	}
	while (getline(shaderFile, line)) {
		filecontent += line + "\n";
	}
	shaderFile.close();
	const char* contents = filecontent.c_str();
	glShaderSource(id, 1, &contents, nullptr);

	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.

		std::cout << shaderPath << endl;
		fatalError("Shaders do not compiled " +
			+printf("%s", &(infoLog[0])));

		glDeleteShader(id); // Don't leak the shader.
		return;
	}
}




GLSProgram::~GLSProgram()
{
}

void GLSProgram::addAtribute(const string atributeName) {
	glBindAttribLocation(programID,
		numAtribute++,
		atributeName.c_str());
}

void GLSProgram::use() {
	glUseProgram(programID);
	for (int i = 0; i < numAtribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}
void GLSProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < numAtribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}