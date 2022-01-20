#include <glad/glad.h>
#include <Screen.h>
#include <Shader.h>
#include <stb_image.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#define  NUM 500
#define PI 3.14159265f
#define R 0.5f

void detVertices(float vertices[]) 
{
    for (int i=0; i<5; i++) 
        for (int j=0; j<NUM; j++) 
            for (int k=0; k<2; k++) 
            {
                vertices[6*NUM*i + 6*j + 3*k] = -1.0f+float(i)*0.5f;
                vertices[6*NUM*i + 6*j + 3*k+1] = -1.0f+float(j+k)*2.0f/NUM;
                vertices[6*NUM*i + 6*j + 3*k+2] = 0; 
                vertices[6*NUM*(i+5) + 6*j + 3*k] = -1.0f+float(j+k)*2.0f/NUM;
                vertices[6*NUM*(i+5) + 6*j + 3*k+1] = -1.0f+float(i)*0.5f;
                vertices[6*NUM*(i+5) + 6*j + 3*k+2] = 0; 
            }
}

void getTransformation() {
}

int main()
{
    using namespace std::this_thread;
    using namespace std::chrono;
    try
    {
        Screen screen(800, 800, "2D Transformations");
        getTransformation();
        Shader program("../src/shaders/vertexShader.vert", "../src/shaders/fragmentShader.frag");

        float vertices[60*NUM];

        detVertices(vertices);
        VAO vao;

        VBO vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        float time = 0, dt = 5*0.000624;
        //press escape to close the screen
        while (screen.isOpen())
        {
            screen.clear(0.0f, 0.0f, 0.0f);
            program.use();
            vao.bind();
            glDrawArrays(GL_LINES, 0, 20*NUM);
            screen.swap();
            screen.pollEvents();
            program.setFloat("dt", (time+=dt));
            if (time >= 1.0f || time <= 0.0f)
                dt *= -1;
        }
    }
    catch (std::string ex)
    {
        std::cout << ex << '\n';
    }
    return 0;
}