#include "Sprite.h"
#include "Vertex.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


GLuint Sprite::compileShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compile error: " << infoLog << "\n";
    }
    return shader;
}
void Sprite::createShader(const std::string& vertexFile, const std::string& fragmentFile) {
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

    std::ifstream vertFile(vertexFile);
    std::ifstream fragFile(fragmentFile);

    if (vertFile.is_open() && fragFile.is_open()) {
        std::stringstream vertBuffer, fragBuffer;
        vertBuffer << vertFile.rdbuf();
        fragBuffer << fragFile.rdbuf();

        vertexSrc = vertBuffer.str();
        fragmentSrc = fragBuffer.str();
    }
    else {
        std::cout << "No se encontraron los shaders. Usando shaders por defecto para este objeto.\n";
        vertexSrc = fallbackVertex;
        fragmentSrc = fallbackFragment;
    }

    GLuint vert = compileShader(GL_VERTEX_SHADER, vertexSrc.c_str());
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragmentSrc.c_str());

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vert);
    glAttachShader(shaderProgram, frag);
    glLinkProgram(shaderProgram);

    glDeleteShader(vert);
    glDeleteShader(frag);
}

Sprite::Sprite()
{
	vboID = 0;
}

Sprite::~Sprite()
{
}

void Sprite::init(float x, float y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    Vertex vertexData[6] = {
        {x, y , 255, 255, 255},
        {x, y + height, 255, 0 ,255},
        {x + width, y},
        {x + width, y},
        {x, y + height},
        {x + width, y + height}
    };


    if (vboID == 0)
        glGenBuffers(1, &vboID);

    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shaders.compileShaders("Shaders/spriteVertexShader.glsl", "Shaders/spriteFragmentShader.glsl");
    //createShader("Shaders/spriteVertexShader.glsl", "Shaders/spriteFragmentShader.glsl");
}

void Sprite::draw()
{
    //glUseProgram(shaderProgram);
    shaders.use();
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    shaders.unuse();
    //glUseProgram(0);
}
