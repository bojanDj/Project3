#include <GLFW/glfw3.h>
#include <windows.h>
#include <gl/GLU.h>
#include <stdio.h>

class Window {
    GLFWwindow* window;
    int width = 600, height = 800;
public:
    GLFWwindow* initWindow();
    void run();
    void drawCube();
};

GLFWwindow* Window::initWindow() {
    if (!glfwInit())
    {
        return NULL;
    }

    window = glfwCreateWindow(height, width, "Cube", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    return window;
}

void Window::drawCube() {
    static float vertices[] =
    {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };

    static GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Window::run() {
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective(60, (double)height / (double)width, 0.1, 100);
        glTranslatef(0, 0, -5);

        static float rot = 0;
        glRotatef(rot, 0, 1, 0);

        drawCube();

        Sleep(1000);
        rot += 3;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

int main(void)
{
    Window win;
    GLFWwindow* window = win.initWindow();    
    win.run();

    return 0;
}