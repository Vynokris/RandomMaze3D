
#include <cstdio>
#include <cmath>
#include <map>
#include <string>
#include <ctime>

#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"
#include "maths.hpp"
#include "bmpLoader.hpp"
#include "camera.hpp"
#include "draw.hpp"
#include "mazeGen.hpp"

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

    // Create a new glfw window.
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Maze", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Load the openGL function pointers.
    loadGLFunctions();

    // Print some info logs.
    printf("GLFW_VERSION: %s\n", glfwGetVersionString());
    printf("GL_VERSION: %s\n",   glGetString(GL_VERSION));
    printf("GL_VENDOR: %s\n",    glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n",  glGetString(GL_RENDERER));

    // Create the camera.
    Camera camera(window, { 0, 0, -5 }, { 0, 0, 0 }, 0.5);
    bool showWireframe = false;
    bool orthographic  = false;

    // Create the maze generator.
    MazeGenerator mazeGen(21, 21);
    srand(time(NULL));
    mazeGen.generate();

    // Load the textures.
    std::map<std::string, GLuint> textures;
    std::string textureNames[] = { "wall", "floor", "ceiling" };
    for (long unsigned int i = 0; i < sizeof(textureNames) / sizeof(textureNames[0]); i++)
        textures[textureNames[i]] = loadTexture(("Resources/Art/" + textureNames[i] + ".bmp").c_str());
    
    // Load the decoration textures.
    /*
    std::map<std::string, GLuint> decorations;
    std::string decorationNames[] = { "vines" };
    for (long unsigned int i = 0; i < sizeof(textureNames) / sizeof(textureNames[0]); i++)
        decorations[decorationNames[i]] = loadTexture(("Resources/Art/" + decorationNames[i] + ".bmp").c_str());
    */


    // Main loop.
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Escape to quit.
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;

        // 1-2 to toggle wireframe.
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
            showWireframe = false;
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            showWireframe = true;
        
        // 3-4 to toggle orthographic view.
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
            orthographic = false;
        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
            orthographic = true;

        // Clear buffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        // Send projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Set the projection to perspective or orthographic.
        if (orthographic)
            glOrtho((float)-screenWidth / 120, (float)screenWidth / 120, (float)-screenHeight / 120, (float)screenHeight / 120, 0.01f, 100.f);
        else
            gluPerspective(90.f, (float)screenWidth / screenHeight, 0.01f, 100.f);
        
        // Send modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glLoadIdentity();

        // Update the camera and apply its transforms to the modelview.
        vector3f prevPos = camera.getPos();
        camera.update();
        if (!mazeGen.isInMaze(camera.getPos()))
            camera.setPos(prevPos);
        camera.applyTransforms();



        // Draw primitive.
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

        // Create an ambient light.
        GLfloat light1_ambient[]  = { 3.5, 3.5, 3.5, 1 };
        glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
        glEnable (GL_LIGHT1);

        // Render the maze geometry.
        mazeGen.render(textures);

        /*
        glPushMatrix();

        // Draw the gizmo in the center.
        gl::drawGizmo(1);

        // Draw the triangle.
        glTranslatef(2, 0, 0);
        gl::drawTriangle(1, textures["Cobblestone1"]);

        // Draw the quad.
        glTranslatef(1.5, 0, 0);
        gl::drawDividedQuad(1, textures["Cobblestone0"]);

        // Draw the cube.
        glTranslatef(1.5, 0, 0);
        gl::drawCube(1, textures["StoneBricks1"]);

        // Draw the cone.
        glTranslatef(1.5, 0, 0);
        glColor3f(31.f/255, 189.f/255, 180.f/255);
        gl::drawCone(10, 0.5, 1);

        // Draw the sphere.
        glTranslatef(2, 0, 0);
        glColor3f(111.f/255, 93.f/255, 215.f/255);
        gl::drawSphere(50, 25, 1);

        // Draw the point sphere.
        glTranslatef(2.5, 0, 0);
        glColor3f(1, 1, 1);
        gl::drawPointSphere(100, 10, 1);

        glPopMatrix();
        */

        glfwSwapBuffers(window);
    }

    // Unload the textures and exit.
    for (auto i = textures.begin(); i != textures.end(); i++)
        glDeleteTextures(1, &i->second);
    glfwTerminate();
    return 0;
}