
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
    int screenWidth  = 2550;
    int screenHeight = 1440;

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

    // Set some openGL parameters.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // Create the camera.
    Camera camera(window, { 0, 10, -5 }, { 0, 0, 0 }, 0.5);
    bool showWireframe = false;
    bool orthographic  = false;

    // Create the maze generator.
    MazeGenerator mazeGen(31, 31);
    srand(time(NULL));
    mazeGen.generate();

    // Load the textures.
    std::map<std::string, GLuint> textures;
    std::string textureNames[] = { "wall", "floor", "ceiling" };
    for (long unsigned int i = 0; i < sizeof(textureNames) / sizeof(textureNames[0]); i++)
        textures[textureNames[i]] = loadBmpTexture(("Resources/Art/" + textureNames[i] + ".bmp").c_str());
    
    // Load the decoration textures.
    /*
    std::map<std::string, GLuint> decorations;
    std::string decorationNames[] = { "vines" };
    for (long unsigned int i = 0; i < sizeof(textureNames) / sizeof(textureNames[0]); i++)
        decorations[decorationNames[i]] = loadTexture(("Resources/Art/" + decorationNames[i] + ".bmp").c_str());
    */

    // Create an ambient light.
    GLfloat light2_ambient[]  = { 1, 1, 1, 1 };
    glLightfv(GL_LIGHT2, GL_AMBIENT,  light2_ambient);

    // Create the camera light.
    GLfloat light1_ambient []            = { 6, 5.5, 3, 1 };
    GLfloat light1_position[]            = { 0, camera.getPos().y, 0, 1 };
    GLfloat light1_constant_attenuation  = 1;
    GLfloat light1_linear_attenuation    = 0.05;
    GLfloat light1_quadratic_attenuation = 0.01;
    glLightfv(GL_LIGHT1, GL_AMBIENT,               light1_ambient);
    glLightfv(GL_LIGHT1, GL_POSITION,              light1_position);
    glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION,  light1_constant_attenuation);
    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION,    light1_linear_attenuation);
    glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, light1_quadratic_attenuation);
    glEnable (GL_LIGHT1);

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
        
        // 5-6 to toggle the light 2.
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
            glDisable(GL_LIGHT2);
        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
            glEnable(GL_LIGHT2);

        // Clear buffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        // Send projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Set the projection to perspective or orthographic.
        if (orthographic)
            glOrtho((float)-screenWidth / 120, (float)screenWidth / 120, (float)-screenHeight / 120, (float)screenHeight / 120, 0.f, 100.f);
        else
            gluPerspective(85.f, (float)screenWidth / screenHeight, 0.01f, 100.f);
        
        // Send modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Update the camera with user input and apply its transforms to the modelview.
        camera.update();
        for (int x = -1; x <= 1; x++);
        if (!mazeGen.isInMaze(camera.getPos())) {
            vector3f vec = mazeGen.backToMazeVec(camera.getPos());
            camera.setPos({ camera.getPos().x + vec.x, camera.getPos().y, camera.getPos().z + vec.z });
        }
        camera.applyTransforms();

        // Draw primitive.
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

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