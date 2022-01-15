#include <glad/glad.h>
#include <Screen.h>
#include <Shader.h>

int main() { 
    try {
        Screen screen(800,600,"2D Transformations");    
        Shader program("../src/shaders/vertexShader.vert", "../src/shaders/fragmentShader.frag");

        float vertices[] = {
            -1.0f,-1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            
            1.0f, 1.0f, 0.0f,
            1.0f,-1.0f, 0.0f,
            -1.0f,-1.0f, 0.0f
        };

        VAO vao;

        VBO vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //press escape to close the screen
        while (screen.isOpen()) {
            screen.clear(0.0f, 0.0f, 0.0f);
            program.use();
            vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            screen.swap();
            screen.pollEvents();
        }
    } catch (std::string ex) {
        std::cout << ex << '\n';
    } 
    return 0;
}