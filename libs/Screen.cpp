#include <Screen.h>

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void frameBufferSizeCallBack(GLFWwindow *window, int width, int height) {
    glViewport(0,0, width, height);
}

Screen::Screen(int width, int height, const std::string &title, float r, float g, float b , float alpha)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to creat window\n";
        exit(-1);
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        exit(-1);
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
}

bool Screen::isOpen() {
    return !glfwWindowShouldClose(window);
}

void Screen::clear(float r, float g, float b, float alpha) {
    glClearColor(r, g, b, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::swap() {
    glfwSwapBuffers(window);
}

void Screen::pollEvents() {
    processInput(window);
    glfwPollEvents();
}

Screen::~Screen() {
    glfwTerminate();
}