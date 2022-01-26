#include "lights.hpp"
#include "mazeGen.hpp"

static GLfloat getCurrentLight(int i)
{
    GLfloat curLight;
    switch (i)
    {
    case 0:
        curLight = GL_LIGHT3;
        break;
    case 1:
        curLight = GL_LIGHT4;
        break;
    case 2:
        curLight = GL_LIGHT5;
        break;
    case 3:
        curLight = GL_LIGHT6;
        break;
    case 4:
        curLight = GL_LIGHT7;
        break;
    case 5:
        curLight = GL_LIGHT0;
        break;
    default:
        throw;
    }
    return curLight;
}

void setupLights()
{
    // Create an ambient light.
    GLfloat light1_ambient[4] = { 1, 1, 1, 1 };
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);

    // Create the camera light.
    GLfloat light2_ambient [4]           = { 15, 14, 6.5, 1 };
    GLfloat light2_position[4]           = { 0, 15, 0, 1 };
    GLfloat light2_constant_attenuation  = 1;
    GLfloat light2_linear_attenuation    = 0.05;
    GLfloat light2_quadratic_attenuation = 0.02;
    glLightfv(GL_LIGHT2, GL_AMBIENT,               light2_ambient);
    glLightfv(GL_LIGHT2, GL_POSITION,              light2_position);
    glLightf (GL_LIGHT2, GL_CONSTANT_ATTENUATION,  light2_constant_attenuation);
    glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION,    light2_linear_attenuation);
    glLightf (GL_LIGHT2, GL_QUADRATIC_ATTENUATION, light2_quadratic_attenuation);
    glEnable (GL_LIGHT2);

    // Create the 5 room lights.
    for (int i = 0; i < 5; i++)
    {
        GLfloat curLight = getCurrentLight(i);
        GLfloat curLight_ambient[4]            = { 7, 6.5, 4, 1 };

        glLightfv(curLight, GL_AMBIENT,               curLight_ambient);
        glLightf (curLight, GL_CONSTANT_ATTENUATION,  light2_constant_attenuation);
        glLightf (curLight, GL_LINEAR_ATTENUATION,    light2_linear_attenuation);
        glLightf (curLight, GL_QUADRATIC_ATTENUATION, light2_quadratic_attenuation);
        glEnable (curLight);
    }

    // Create the exit light.
    GLfloat exitLight_ambient[4]  = { 7, 1, 0, 1 };
    GLfloat exitLight_diffuse[4]  = { 0, 0, 0, 1 };
    GLfloat exitLight_specular[4] = { 0, 0, 0, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT,               exitLight_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,               exitLight_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,              exitLight_specular);
    glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light2_constant_attenuation);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION,    light2_linear_attenuation);
    glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light2_quadratic_attenuation);
    glEnable (GL_LIGHT0);
}

void updateLights(GLFWwindow* window, const MazeGenerator& mazeGen, const GLuint& lightTexture)
{
    // 5-6 to toggle the light 1.
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        glDisable(GL_LIGHT1);
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        glEnable(GL_LIGHT1);

    // 7-8 to toggle the light 2.
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        glDisable(GL_LIGHT2);
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        glEnable(GL_LIGHT2);

    // Move the 5 room lights according to the camera transforms.
    for (int i = 0; i < 5; i++)
    {
        GLfloat curLight = getCurrentLight(i);

        vector2i curRoom   = mazeGen.getRoomCoords(i);
        vector2i startTile = mazeGen.getMazeStart();
        int tileSize       = mazeGen.tileSize;

        GLfloat curLight_position[4] = 
        { 
            (float)(curRoom.x - startTile.x) * tileSize, 
            12, 
            (float)(curRoom.y - startTile.y) * tileSize - tileSize/2, 
            1 
        };

        glLightfv(curLight, GL_POSITION, curLight_position);
    }

    // Move the exit room according to camera transforms.
    GLfloat exitLight_position[4] = 
    { 
        (GLfloat)((mazeGen.getMazeEnd().x - mazeGen.getMazeStart().x) * mazeGen.tileSize), 
        12, 
        (GLfloat)((mazeGen.getMazeEnd().y - mazeGen.getMazeStart().y) * mazeGen.tileSize - mazeGen.tileSize), 
        1 
    };
    glLightfv(GL_LIGHT0, GL_POSITION, exitLight_position);
}

void updateLightColor(const int& lightID)
{
    GLfloat curLight = getCurrentLight(lightID);
    GLfloat curLight_ambient[4] = { 0, 7, 1, 1 };
    if (lightID == 5) {
        curLight_ambient[1] = 0;
        curLight_ambient[2] = 20;
    }
    glLightfv(curLight, GL_AMBIENT, curLight_ambient);
}
