
#include <cstdio>
#include <cmath>
#include <map>
#include <string>
#include <ctime>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"
#include "maths.hpp"
#include "bmpLoader.hpp"
#include "camera.hpp"
#include "lights.hpp"
#include "interactable.hpp"
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
    bool collisions    = true;

    // Create the maze generator.
    MazeGenerator mazeGen(25, 25);
    srand(time(NULL));
    mazeGen.generate();

    // Create interactable objects for the chests.
    Interactable chests[5];
    bool         chestsOpened[5];
    for (int i = 0; i < 5; i++)
    {
        vector2f roomPos = { (float)(mazeGen.getRoomCoords(i).x - mazeGen.getMazeStart().x) * mazeGen.tileSize, 
                             (float)(mazeGen.getRoomCoords(i).y - mazeGen.getMazeStart().y) * mazeGen.tileSize - mazeGen.tileSize/2, };
        chests[i].setPos({ roomPos.x, 5, roomPos.y });
    }

    // Create the scene lights.
    setupLights();

    // Load the textures.
    std::map<std::string, GLuint> textures;
    std::string textureNames[] = { "wall", "floor", "ceiling", "light", "door0", "door1", "chest0", "chest1", "chest2" };
    for (long unsigned int i = 0; i < sizeof(textureNames) / sizeof(textureNames[0]); i++)
        textures[textureNames[i]] = loadBmpTexture(("Resources/Art/" + textureNames[i] + ".bmp").c_str());



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
        
        // 9-0 to toggle collisions.
        if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
            collisions = true;
        else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
            collisions = false;



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
            gluPerspective(85.f, (float)screenWidth / screenHeight, 0.01f, 270.f);



        // Send modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Update the camera with user input.
        camera.update();

        // Keep the player in-bounds.
        if (collisions && !mazeGen.isInMaze(camera.getPos())) 
        {
            vector3f vec = mazeGen.backToMazeVec(camera.getPos());
            camera.setPos({ camera.getPos().x + vec.x, camera.getPos().y, camera.getPos().z + vec.z });
        }

        // Apply the camera's transforms to the model view.
        camera.applyTransforms();

        // Update the chests.
        bool allChestsOpened = true;
        for (int i = 0; i < 5; i++) 
        {
            if (chests[i].interaction(window, camera.getPos())) 
            {
                chests[i].setActive(false);
                chestsOpened[i] = true;
                updateLightColor(i);
            }
            if (!chestsOpened[i]) {
                allChestsOpened = false;
            }
        }
        if (allChestsOpened)
        {
            updateLightColor(5);
        }

        // Draw primitive.
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

        // Update the scene lights.
        updateLights(window, mazeGen, textures["light"]);

        // Render the maze geometry.
        mazeGen.render(textures, allChestsOpened);



        // Disable collisions when the player gets out of the maze.
        if (allChestsOpened)
        {
            vector3f endPos = {
                (float)(mazeGen.getMazeEnd().x - mazeGen.getMazeStart().x) * mazeGen.tileSize, 
                10, 
                (float)(mazeGen.getMazeEnd().y - mazeGen.getMazeStart().y) * mazeGen.tileSize - mazeGen.tileSize * 1.5f
            };

            if (endPos.x - mazeGen.tileSize/2 <= camera.getPos().x && camera.getPos().x <= endPos.x + mazeGen.tileSize/2 && 
                endPos.z - mazeGen.tileSize/2 <= camera.getPos().z && camera.getPos().z <= endPos.z + mazeGen.tileSize/2)
            {
                collisions = false;
                glEnable(GL_LIGHT1);
            }
        }

        glfwSwapBuffers(window);
    }

    // Unload the textures and exit.
    for (auto i = textures.begin(); i != textures.end(); i++)
        glDeleteTextures(1, &i->second);
    glfwTerminate();
    return 0;
}