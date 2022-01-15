#ifndef SCREEN_H
#define SCREEN_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

void processInput(GLFWwindow *window);

void frameBufferSizeCallBack(GLFWwindow *window, int width, int height);

class Screen
{
private:
    GLFWwindow *window;

public:
    Screen(int width, int height, const std::string &title, float r = 0.0f, float g = 0.0f, float b = 1.0f, float alpha = 1.0f);

    bool isOpen();

    void clear(float r, float g, float b, float alpha = 1.0f);

    void swap();

    void pollEvents();

    ~Screen();
};
#endif