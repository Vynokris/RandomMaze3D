
#include <cstdio>
#include <cmath>
#include <map>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gl.hpp"
#include "glUtility.hpp"
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
    bool orthographic  = false;
    float speed = 0.1f;
    double mousePos[2];
    glfwGetCursorPos(window, &mousePos[0], &mousePos[1]);
    float3 cameraPos = { 5.5f, 0, 5.5f };
    float3 cameraRot = { 0.f, 0.f, 0.f };

    std::map<std::string, GLuint> textures;
    std::string textureNames[5] = { "Cobblestone0", "Cobblestone1", "StoneBricks0", "StoneBricks1", "Stonebricks2" };
    for (long unsigned int i = 0; i < sizeof(textureNames) / sizeof(textureNames[0]); i++)
        textures[textureNames[i]] = loadTexture(("Resources/Art/" + textureNames[i] + ".bmp").c_str(), 16, 16);

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

        // WASD, space & shift keys to move the camera.
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            float3 lookAtPoint = getSphericalCoords(speed, DEG2RAD*(360 - cameraRot.y + 90), DEG2RAD*(360 - cameraRot.x - 90));
            cameraPos.x += lookAtPoint.x; cameraPos.y += lookAtPoint.y; cameraPos.z += lookAtPoint.z;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            float3 lookAtPoint = getSphericalCoords(speed, DEG2RAD*(360 - cameraRot.y + 90), DEG2RAD*(360 - cameraRot.x - 90));
            cameraPos.x -= lookAtPoint.x; cameraPos.y -= lookAtPoint.y; cameraPos.z -= lookAtPoint.z;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            float3 lookAtPoint = getSphericalCoords(speed, DEG2RAD*90, DEG2RAD*(360 - cameraRot.x));
            cameraPos.x -= lookAtPoint.x; cameraPos.y -= lookAtPoint.y; cameraPos.z -= lookAtPoint.z;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            float3 lookAtPoint = getSphericalCoords(speed, DEG2RAD*90, DEG2RAD*(360 - cameraRot.x));
            cameraPos.x += lookAtPoint.x; cameraPos.y += lookAtPoint.y; cameraPos.z += lookAtPoint.z;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            float3 lookAtPoint = getSphericalCoords(speed, DEG2RAD*(360 - cameraRot.y), DEG2RAD*(360 - cameraRot.x - 90));
            cameraPos.x += lookAtPoint.x; cameraPos.y += lookAtPoint.y; cameraPos.z += lookAtPoint.z;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            float3 lookAtPoint = getSphericalCoords(speed, DEG2RAD*(360 - cameraRot.y), DEG2RAD*(360 - cameraRot.x - 90));
            cameraPos.x -= lookAtPoint.x; cameraPos.y -= lookAtPoint.y; cameraPos.z -= lookAtPoint.z;
        }

        // Mouse to rotate the camera on X and Y.
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            double newMousePos[2]; 
            glfwGetCursorPos(window, &newMousePos[0], &newMousePos[1]);

            cameraRot.x -= (newMousePos[0] - mousePos[0]) / 7;
            cameraRot.y -= (newMousePos[1] - mousePos[1]) / 7;

            glfwSetCursorPos(window, mousePos[0], mousePos[1]);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwGetCursorPos(window, &mousePos[0], &mousePos[1]);
        }

        // Clear buffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        // Send projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (orthographic)
            glOrtho((float)-screenWidth / 120, (float)screenWidth / 120, (float)-screenHeight / 120, (float)screenHeight / 120, 0.01f, 100.f);
        else
            gluPerspective(90.f, (float)screenWidth / screenHeight, 0.01f, 100.f);
        
        // Send modelview matrix.
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();

        // Move the modelview matrix to match the camera position and rotation.
        glRotatef   (-cameraRot.y, 1.f, 0.f, 0.f);
        glRotatef   (-cameraRot.x, 0.f, 1.f, 0.f);
        glRotatef   (-cameraRot.z, 0.f, 0.f, 1.f);
        glTranslatef(-cameraPos.x, -cameraPos.y, -cameraPos.z);

        // Draw primitive
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);

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
        glColor3f(31.f/255, 189.f/255, 180.f/255);
        glTranslatef(1.5, 0, 0);
        gl::drawCone(10, 0.5, 1);

        // Draw the sphere.
        glColor3f(111.f/255, 93.f/255, 215.f/255);
        glTranslatef(2, 0, 0);
        gl::drawSphere(10, 10, 1);

        // Draw the point sphere.
        glColor3f(1, 1, 1);
        glTranslatef(2.5, 0, 0);
        gl::drawPointSphere(100, 10, 1);

        glPopMatrix();

        glfwSwapBuffers(window);
    }

    for (auto i = textures.begin(); i != textures.end(); i++)
        glDeleteTextures(1, &i->second);
    glfwTerminate();
    return 0;
}