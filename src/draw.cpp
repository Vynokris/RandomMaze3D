#include "gl.hpp"
#include "maths.hpp"
#include "draw.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void gl::drawTriangle(const float& size, const GLuint& texture)
{
    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);
    {
        glTexCoord2f(0, 0); glVertex3f(-size/2,  size/2, 0.f);
        glTexCoord2f(0, 1); glVertex3f(-size/2, -size/2, 0.f);
        glTexCoord2f(1, 0); glVertex3f( size/2,  size/2, 0.f);
    }
    glEnd();

    if (texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void gl::drawQuad(const float& size, const GLuint& texture)
{
    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0); glVertex3f(-size/2,  size/2, 0.f);
        glTexCoord2f(1, 0); glVertex3f( size/2,  size/2, 0.f);
        glTexCoord2f(1, 1); glVertex3f( size/2, -size/2, 0.f);
        glTexCoord2f(0, 1); glVertex3f(-size/2, -size/2, 0.f);
    }
    glEnd();

    if (texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void gl::drawDividedQuad(const float& size, const GLuint& texture, const bool& negateNormals)
{
    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);
    {
        glNormal3f(0, 0, (negateNormals ? 1 : -1)); glTexCoord2f(0, 0); glVertex3f(-size/2,  size/2, 0.f);
        glNormal3f(0, 0, (negateNormals ? 1 : -1)); glTexCoord2f(0, 1); glVertex3f(-size/2, -size/2, 0.f);
        glNormal3f(0, 0, (negateNormals ? 1 : -1)); glTexCoord2f(1, 0); glVertex3f( size/2,  size/2, 0.f);
        
        glNormal3f(0, 0, (negateNormals ? 1 : -1)); glTexCoord2f(1, 1); glVertex3f( size/2, -size/2, 0.f);
        glNormal3f(0, 0, (negateNormals ? 1 : -1)); glTexCoord2f(1, 0); glVertex3f( size/2,  size/2, 0.f);
        glNormal3f(0, 0, (negateNormals ? 1 : -1)); glTexCoord2f(0, 1); glVertex3f(-size/2, -size/2, 0.f);
    }
    glEnd();

    if (texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void gl::drawCube(const float& size, const GLuint& texture)
{
    glPushMatrix();

    glTranslatef(0, 0, size/2);

    // Render the 4 side faces.
    for (int i = 0; i < 4; i++)
    {
        glRotatef(-90, 0, 1, 0);
        glTranslatef(-size/2, 0, size/2);
        drawDividedQuad(size, texture, true);
    }

    // Render the upper and lower faces.
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -size/2, -size/2);
    drawDividedQuad(size, texture, true);
    glTranslatef(0, 0, size);
    drawDividedQuad(size, texture);

    glPopMatrix();
}

void gl::drawSubdividedCube(const float& size, const int& resX, const int& resY, const int& resZ)
{
    glBegin(GL_TRIANGLES);

    for (int x = 0; x < resX + 1; x++)
    {
        for (int y = 0; y < resY + 1; y++)
        {
            for (int z = 0; z < resZ + 1; z++)
            {
                vector3f curCoords = { - size / 2 + (size / resX) * x, 
                                     - size / 2 + (size / resY) * y, 
                                     - size / 2 + (size / resZ) * z };

                // Left and right faces.
                if ((x == 0 || x == resX) && y < resY && z < resZ)
                {
                    float xPos = (x == 0 ? -size / 2 : size / 2);

                    glTexCoord2f(0, 0); glVertex3f(xPos, curCoords.y,                 curCoords.z);
                    glTexCoord2f(0, 1); glVertex3f(xPos, curCoords.y + (size / resY), curCoords.z + (size / resZ));
                    glTexCoord2f(1, 0); glVertex3f(xPos, curCoords.y + (size / resY), curCoords.z);

                    glVertex3f(xPos, curCoords.y,                 curCoords.z);
                    glVertex3f(xPos, curCoords.y,                 curCoords.z + (size / resZ));
                    glVertex3f(xPos, curCoords.y + (size / resY), curCoords.z + (size / resZ));
                }

                // Up and down faces.
                if ((y == 0 || y == resY) && x < resX && z < resZ)
                {
                    float yPos = (y == 0 ? -size / 2 : size / 2);

                    glVertex3f(curCoords.x,                 yPos, curCoords.z);
                    glVertex3f(curCoords.x,                 yPos, curCoords.z + (size / resZ));
                    glVertex3f(curCoords.x + (size / resX), yPos, curCoords.z + (size / resZ));

                    glVertex3f(curCoords.x,                 yPos, curCoords.z);
                    glVertex3f(curCoords.x + (size / resX), yPos, curCoords.z + (size / resZ));
                    glVertex3f(curCoords.x + (size / resX), yPos, curCoords.z);
                }

                // Front and back faces.
                if ((z == 0 || z == resZ) && x < resX && y < resY)
                {
                    float zPos = (z == 0 ? -size / 2 : size / 2);

                    glVertex3f(curCoords.x,                 curCoords.y,                 zPos);
                    glVertex3f(curCoords.x,                 curCoords.y + (size / resY), zPos);
                    glVertex3f(curCoords.x + (size / resX), curCoords.y + (size / resY), zPos);
                    
                    glVertex3f(curCoords.x,                 curCoords.y,                 zPos);
                    glVertex3f(curCoords.x + (size / resX), curCoords.y + (size / resY), zPos);
                    glVertex3f(curCoords.x + (size / resX), curCoords.y,                 zPos);
                }
            }
        }
    }
    glEnd();
}

void gl::drawSphere(const float& r, const int& lon, const int& lat)
{
    glBegin(GL_TRIANGLES);

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j+0) / (float)lat) * PI;
        float theta1 = ((j+1) / (float)lat) * PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i+0) / (float)lon) * 2.f * PI;
            float phi1 = ((i+1) / (float)lon) * 2.f * PI;

            vector3f c0 = getSphericalCoords(r, theta0, phi0);
            vector3f c1 = getSphericalCoords(r, theta0, phi1);
            vector3f c2 = getSphericalCoords(r, theta1, phi1);
            vector3f c3 = getSphericalCoords(r, theta1, phi0);

            glVertex3f(c0.x, c0.y, c0.z);
            glVertex3f(c1.x, c1.y, c1.z);
            glVertex3f(c2.x, c2.y, c2.z);
            
            glVertex3f(c0.x, c0.y, c0.z);
            glVertex3f(c2.x, c2.y, c2.z);
            glVertex3f(c3.x, c3.y, c3.z);
        }
    }
    glEnd();
}

void gl::drawPointSphere(const float& r, const int& lon, const int& lat)
{
    glBegin(GL_POINTS);

    for (int j = 0; j < lat; ++j)
    {
        float theta = (j / (float)lat) * PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi = (i / (float)lon) * 2.f * PI;

            vector3f coords = getSphericalCoords(r, theta, phi);

            glVertex3f(coords.x, coords.y, coords.z);
        }
    } 
    glEnd();
}

void gl::drawHelperSphere(const float& r, const float& theta, const float& phi)
{
    glColor3f(1, 1, 1);
    drawPointSphere(r, 20, 20);

    glDisable(GL_DEPTH_TEST);
    vector3f coords = getSphericalCoords(r, theta, phi);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 1);
    glVertex3f(coords.x, coords.y, coords.z);
    glEnd();
    glColor3f(1, 1, 1);
    glEnable(GL_DEPTH_TEST);
}


void gl::drawCone(const float& r, const float& h, const int& res)
{
    glRotatef(90, -1.f, 0.f, 0.f);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < res; i++)
    {
        // Draw the base circle.
        glVertex3f(0.f, 0.f, 0.f);
        for (int j = 0; j < 2; j++)
        {
            float theta = ((i + j) / (float)res) * 2.f * PI;

            vector3f coords = getSphericalCoords(r, theta, 0);

            glVertex3f(coords.x, coords.y, coords.z);
        }

        // Draw the side triangles.
        glVertex3f(0.f, 0.f, h);
        for (int j = 0; j < 2; j++)
        {
            float theta = ((i + j) / (float)res) * 2.f * PI;

            vector3f coords = getSphericalCoords(r, theta, 0);

            glVertex3f(coords.x, coords.y, coords.z);
        }
    }
    
    glEnd();
    glRotatef(90, 1.f, 0.f, 0.f);
}


void gl::drawGizmo(const float& scale)
{
    // Draw the x cone.
    glColor3f    (1.f, 0.f, 0.f);
    glRotatef(90, 0.f, 0.f, -1.f);
    glTranslatef (0.f, scale, 0.f);
    drawCone(0.05 * scale, 0.1 * scale, 20.f);
    glTranslatef (0.f, -scale, 0.f);
    glRotatef(90, 0.f, 0.f, 1.f);

    // Draw the y cone.
    glColor3f    (0.f, 1.f, 0.f);
    glRotatef(90, 0.f, 1.f, 0.f);
    glTranslatef (0.f, scale, 0.f);
    drawCone(0.05 * scale, 0.1 * scale, 20.f);
    glTranslatef (0.f, -scale, 0.f);
    glRotatef(90, 0.f, -1.f, 0.f);

    // Draw the z cone.
    glColor3f    (0.f, 0.f, 1.f);
    glRotatef(90, 1.f, 0.f, 0.f);
    glTranslatef (0.f, scale, 0.f);
    drawCone(0.05 * scale, 0.1 * scale, 20.f);
    glTranslatef (0.f, -scale, 0.f);
    glRotatef(90, -1.f, 0.f, 0.f);


    glBegin(GL_LINES);

    // Draw the x line.
    glColor3f (1.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(scale, 0.f, 0.f);

    // Draw the y line.
    glColor3f (0.f, 1.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, scale, 0.f);

    // Draw the z line.
    glColor3f (0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, scale);

    glEnd();

    glColor3f(1.f, 1.f, 1.f);
}

void gl::testDrawShape(GLFWwindow* window, const vector3f& rotation, const GLint& texture)
{
    // Get the current shape in function of the pressed keys.
    static int shape = -1;
    if (glfwGetKey(window, GLFW_KEY_KP_DECIMAL))
        shape = -1;
    if (glfwGetKey(window, GLFW_KEY_KP_0))
        shape = 0;
    if (glfwGetKey(window, GLFW_KEY_KP_1))
        shape = 1;
    if (glfwGetKey(window, GLFW_KEY_KP_2))
        shape = 2;
    if (glfwGetKey(window, GLFW_KEY_KP_3))
        shape = 3;
    if (glfwGetKey(window, GLFW_KEY_KP_4))
        shape = 4;
    if (glfwGetKey(window, GLFW_KEY_KP_5))
        shape = 5;
    if (glfwGetKey(window, GLFW_KEY_KP_6))
        shape = 6;
    if (glfwGetKey(window, GLFW_KEY_KP_7))
        shape = 7;
    if (glfwGetKey(window, GLFW_KEY_KP_8))
        shape = 8;
    if (glfwGetKey(window, GLFW_KEY_KP_9))
        shape = 9;
    
    // Show or hide colors.
    if (shape == 9 || shape == 7)
        glEnable(GL_COLOR_MATERIAL); // This causes the lighting to be brighter.
    else
        glDisable(GL_COLOR_MATERIAL); // This doesn't fix the brighter lighting.

    glPushMatrix();

    glTranslatef(0, 0, -1);
    glRotatef(-rotation.x, 0, 1, 0);
    glRotatef(-rotation.y, 1, 0, 0);
    glRotatef(-rotation.z, 0, 0, 1);

    switch (shape)
    {
    case 0:
        drawTriangle(0.5, texture);
        break;
    case 1:
        drawQuad(0.5, texture);
        break;
    case 2:
        drawDividedQuad(0.5, texture);
        break;
    case 3:
        drawCube(0.5, texture);
        break;
    case 4:
        drawSubdividedCube(0.5, 5, 5, 5);
        break;
    case 5:
        drawSphere(0.5, 10, 10);
        break;
    case 6:
        drawPointSphere(0.5, 10, 10);
        break;
    case 7:
        drawHelperSphere(0.5, DEG2RAD*90, DEG2RAD*(360 - rotation.x - 90));
        break;
    case 8:
        drawCone(0.2, 0.5, 10);
        break;
    case 9:
        drawGizmo(0.5);
        break;
    case 10:
        break;
    default: 
        break;
    }

    glPopMatrix();
}
