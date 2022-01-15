#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader {
private:
    unsigned int shaderProgram;
public:
    Shader(const std::string& vsFileName, const std::string& fsFileName);
    void use();
    ~Shader();
};

class VAO {
private:
    unsigned int vao;
public:
    VAO();
    void bind();
    ~VAO();
};

class VBO {
private:
    unsigned int vbo;
public:
    VBO(float vertices[], unsigned int size, GLenum drawMode);
    ~VBO();
};
#endif