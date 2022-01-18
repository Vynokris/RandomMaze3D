
#include <cstdio>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"
#include "draw.hpp"

int main(int argc, char* argv[])
{
    int screenWidth  = 800;
    int screenHeight = 600;

    if (!glfwInit())
        return -1;
    
    // Target OpenGL 3.3 API in Compatibility mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Add debug flag in case we want to debug it
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Intro", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    loadGLFunctions();

    printf("GLFW_VERSION: %s\n", glfwGetVersionString());
    printf("GL_VERSION: %s\n",  glGetString(GL_VERSION));
    printf("GL_VENDOR: %s\n",   glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    bool showWireframe = false;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        // F1-F2 to toggle wireframe
        if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
            showWireframe = false;
        else if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
            showWireframe = true;

        // Clear buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.f, 0.5f, 0.5f, 1.f);

        // Send projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.f, (float)screenWidth / screenHeight, 0.5f, 100.f);
        
        // Send modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(-5.5f, 0.f, -5.f);
        static float rotation = 0.f;
        rotation += 0.5f;
        glRotatef(rotation, 1.f, 0.f, 0.f);

        // Draw primitive
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

        // Draw the gizmo in the center.
        gl::drawGizmo(1);

        // Draw the triangle.
        glColor3f(247.f/255, 253.f/255, 26.f/255);
        glTranslatef(2.f, 0.f, 0.f);
        gl::drawTriangle(0.5f);

        // Draw the quad.
        glColor3f(227.f/255, 48.f/255, 177.f/255);
        glTranslatef(1.5f, 0.f, 0.f);
        gl::drawQuad(0.5f);

        // Draw the cube.
        glColor3f(11.f/255, 213.f/255, 51.f/255);
        glTranslatef(1.5f, 0.f, 0.f);
        gl::drawCube(2, 2, 2, 1.f);

        // Draw the cone.
        glColor3f(31.f/255, 189.f/255, 180.f/255);
        glTranslatef(1.5f, 0.f, 0.f);
        gl::drawCone(10.f, 0.5f, 1.f);

        // Draw the sphere.
        glColor3f(111.f/255, 93.f/255, 215.f/255);
        glTranslatef(2.f, 0.f, 0.f);
        gl::drawSphere(10.f, 10.f, 1.f);

        // Draw the point sphere.
        glColor3f(0.f, 0.f, 0.f);
        glTranslatef(2.5f, 0.f, 0.f);
        gl::drawPointSphere(10.f, 10.f, 1.f);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}