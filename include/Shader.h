#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader
{
public:
    unsigned int shaderProgram;

    Shader(const std::string &vsFileName, const std::string &fsFileName);
    void use();
    void setInt(const char* name, int value);
    void setFloat(const char* name, float value);
    ~Shader();
};

class VAO
{
private:
    unsigned int vao;

public:
    VAO();
    void bind();
    ~VAO();
};

class VBO
{
private:
    unsigned int vbo;

public:
    VBO(float vertices[], unsigned int size, GLenum drawMode);
    ~VBO();
};
#endif