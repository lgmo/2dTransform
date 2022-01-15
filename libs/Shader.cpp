#include <Shader.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

char *readShaderFile(const std::string &shaderFileName)
{
    char *buffer;
    int length;
    FILE *shaderFile = fopen(shaderFileName.c_str(), "rt");

    if (shaderFile)
    {
        fseek(shaderFile, 0, SEEK_END);
        length = ftell(shaderFile);
        fseek(shaderFile, 0, SEEK_SET);
        buffer = (char *)malloc(length + 1);
        if (buffer)
            fread(buffer, 1, length, shaderFile);
        else
        {
            fclose(shaderFile);
            throw std::string("Unable to read ") + shaderFileName;
        }
    }
    else
    {
        throw std::string("Unable to open ") + shaderFileName;
    }
    fclose(shaderFile);
    buffer[length] = '\0';
    return buffer;
}

Shader::Shader(const std::string &vsFileName, const std::string &fsFileName)
{
    char *vertexShaderSource = readShaderFile(vsFileName);
    char *fragmentShaderSource = readShaderFile(fsFileName);

    int success;
    char infolog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    free(vertexShaderSource);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, GL_COMPILE_STATUS, NULL, infolog);
        ;
        free(fragmentShaderSource);
        throw std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED\nError: ") + infolog;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    free(fragmentShaderSource);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, GL_COMPILE_STATUS, NULL, infolog);
        ;
        throw std::string("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\nError: ") + infolog;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, GL_LINK_STATUS, NULL, infolog);
        ;
        throw std::string("ERROR::SHADER::PROGRAM::LINKING_FAILED\nError: ") + infolog;
    }
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

void Shader::setInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(shaderProgram, name), value); 
}

void Shader::setFloat(const char *name, float value) {
    glUniform1f(glGetUniformLocation(shaderProgram, name), value); 
}

Shader::~Shader()
{
    glDeleteShader(shaderProgram);
}

VAO::VAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void VAO::bind()
{
    glBindVertexArray(vao);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &vao);
}

VBO::VBO(float *vertices, unsigned int size, GLenum drawMode)
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, drawMode);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &vbo);
}