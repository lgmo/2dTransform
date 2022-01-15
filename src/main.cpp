#include <glad/glad.h>
#include <Screen.h>
#include <Shader.h>
#include <stb_image.h>
#include <iostream>

int main()
{
    try
    {
        Screen screen(800, 600, "2D Transformations");
        Shader program("../src/shaders/vertexShader.vert", "../src/shaders/fragmentShader.frag");



        float vertices[] = {
            //positions           //textures
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
             1.0f,  1.0f, 0.0f,   1.0f, 1.0f,

             1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f

        };

        VAO vao;

        VBO vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int texture1;
        glGenTextures(1, &texture1);

        glBindTexture(GL_TEXTURE_2D, texture1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("../img/picture.ppm", &width, &height, &nrChannels, 0);
        
        if (!data)
            throw std::string("Failed to load texture");
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        program.use();
        program.setInt("texture1", 0);
        //press escape to close the screen
        while (screen.isOpen())
        {
            screen.clear(0.0f, 0.0f, 0.0f);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            program.use();
            vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            screen.swap();
            screen.pollEvents();
        }
    }
    catch (std::string ex)
    {
        std::cout << ex << '\n';
    }
    return 0;
}