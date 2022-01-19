#include "gl.hpp"
#include "glUtility.hpp"
#include "draw.hpp"

void gl::drawTriangle(float size, GLuint texture)
{
    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0, 0); glVertex3f(-size,  size, 0.f);
    glTexCoord2f(0, 1); glVertex3f(-size, -size, 0.f);
    glTexCoord2f(1, 0); glVertex3f( size,  size, 0.f);
    glEnd();

    if (texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void gl::drawQuad(float size, GLuint texture)
{
    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-size,  size, 0.f);
    glTexCoord2f(1, 0); glVertex3f( size,  size, 0.f);
    glTexCoord2f(1, 1); glVertex3f( size, -size, 0.f);
    glTexCoord2f(0, 1); glVertex3f(-size, -size, 0.f);
    glEnd();

    if (texture)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

#include <iostream>
void gl::drawCube(int resX, int resY, int resZ, float size)
{
    glBegin(GL_TRIANGLES);

    for (int x = 0; x < resX + 1; x++)
    {
        for (int y = 0; y < resY + 1; y++)
        {
            for (int z = 0; z < resZ + 1; z++)
            {
                float3 curCoords = { - size / 2 + (size / resX) * x, 
                                     - size / 2 + (size / resY) * y, 
                                     - size / 2 + (size / resZ) * z };

                // Left and right faces.
                if ((x == 0 || x == resX) && y < resY && z < resZ)
                {
                    glVertex3f((x == 0 ? -size / 2 : size / 2), curCoords.y,                 curCoords.z);
                    glVertex3f((x == 0 ? -size / 2 : size / 2), curCoords.y,                 curCoords.z + (size / resZ));
                    glVertex3f((x == 0 ? -size / 2 : size / 2), curCoords.y + (size / resY), curCoords.z + (size / resZ));
                    
                    glVertex3f((x == 0 ? -size / 2 : size / 2), curCoords.y,                 curCoords.z);
                    glVertex3f((x == 0 ? -size / 2 : size / 2), curCoords.y + (size / resY), curCoords.z + (size / resZ));
                    glVertex3f((x == 0 ? -size / 2 : size / 2), curCoords.y + (size / resY), curCoords.z);
                }

                // Up and down faces.
                if ((y == 0 || y == resY) && x < resX && z < resZ)
                {
                    glVertex3f(curCoords.x,                 (y == 0 ? -size / 2 : size / 2), curCoords.z);
                    glVertex3f(curCoords.x,                 (y == 0 ? -size / 2 : size / 2), curCoords.z + (size / resZ));
                    glVertex3f(curCoords.x + (size / resX), (y == 0 ? -size / 2 : size / 2), curCoords.z + (size / resZ));

                    glVertex3f(curCoords.x,                 (y == 0 ? -size / 2 : size / 2), curCoords.z);
                    glVertex3f(curCoords.x + (size / resX), (y == 0 ? -size / 2 : size / 2), curCoords.z + (size / resZ));
                    glVertex3f(curCoords.x + (size / resX), (y == 0 ? -size / 2 : size / 2), curCoords.z);
                }

                // Front and back faces.
                if ((z == 0 || z == resZ) && x < resX && y < resY)
                {
                    glVertex3f(curCoords.x,                 curCoords.y,                 (z == 0 ? -size / 2 : size / 2));
                    glVertex3f(curCoords.x,                 curCoords.y + (size / resY), (z == 0 ? -size / 2 : size / 2));
                    glVertex3f(curCoords.x + (size / resX), curCoords.y + (size / resY), (z == 0 ? -size / 2 : size / 2));
                    
                    glVertex3f(curCoords.x,                 curCoords.y,                 (z == 0 ? -size / 2 : size / 2));
                    glVertex3f(curCoords.x + (size / resX), curCoords.y + (size / resY), (z == 0 ? -size / 2 : size / 2));
                    glVertex3f(curCoords.x + (size / resX), curCoords.y,                 (z == 0 ? -size / 2 : size / 2));
                }
            }
        }
    }
    glEnd();
}

void gl::drawSphere(int lon, int lat, float r)
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

            float3 c0 = getSphericalCoords(r, theta0, phi0);
            float3 c1 = getSphericalCoords(r, theta0, phi1);
            float3 c2 = getSphericalCoords(r, theta1, phi1);
            float3 c3 = getSphericalCoords(r, theta1, phi0);

            glVertex3f(c0.x, c0.y, c0.z);
            glVertex3f(c1.x, c1.y, c1.z);
            glVertex3f(c2.x, c2.y, c2.z);
            
            if (0 < j && j < lat - 1)
            {
                glVertex3f(c0.x, c0.y, c0.z);
                glVertex3f(c2.x, c2.y, c2.z);
                glVertex3f(c3.x, c3.y, c3.z);
            }
        }
    }
    glEnd();
}

void gl::drawPointSphere(int lon, int lat, float r)
{
    glBegin(GL_POINTS);

    for (int j = 0; j < lat; ++j)
    {
        float theta = (j / (float)lat) * PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi = (i / (float)lon) * 2.f * PI;

            float3 coords = getSphericalCoords(r, theta, phi);

            glVertex3f(coords.x, coords.y, coords.z);
        }
    } 
    glEnd();
}

void gl::drawHelperSphere(float r, float theta, float phi)
{
    glColor3f(1, 1, 1);
    gl::drawPointSphere(20, 20, r);

    float3 coords = getSphericalCoords(r, theta, phi);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 1);
    glVertex3f(coords.x, coords.y, coords.z);
    glEnd();
}


void gl::drawCone(int res, float r, float h)
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

            float3 coords = getSphericalCoords(r, theta, 0);

            glVertex3f(coords.x, coords.y, coords.z);
        }

        // Draw the side triangles.
        glVertex3f(0.f, 0.f, h);
        for (int j = 0; j < 2; j++)
        {
            float theta = ((i + j) / (float)res) * 2.f * PI;

            float3 coords = getSphericalCoords(r, theta, 0);

            glVertex3f(coords.x, coords.y, coords.z);
        }
    }
    
    glEnd();
    glRotatef(90, 1.f, 0.f, 0.f);
}


void gl::drawGizmo(float scale)
{
    // Draw the x cone.
    glColor3f    (1.f, 0.f, 0.f);
    glRotatef(90, 0.f, 0.f, -1.f);
    glTranslatef (0.f, scale, 0.f);
    drawCone(20.f, 0.05 * scale, 0.1 * scale);
    glTranslatef (0.f, -scale, 0.f);
    glRotatef(90, 0.f, 0.f, 1.f);

    // Draw the y cone.
    glColor3f    (0.f, 1.f, 0.f);
    glRotatef(90, 0.f, 1.f, 0.f);
    glTranslatef (0.f, scale, 0.f);
    drawCone(20.f, 0.05 * scale, 0.1 * scale);
    glTranslatef (0.f, -scale, 0.f);
    glRotatef(90, 0.f, -1.f, 0.f);

    // Draw the z cone.
    glColor3f    (0.f, 0.f, 1.f);
    glRotatef(90, 1.f, 0.f, 0.f);
    glTranslatef (0.f, scale, 0.f);
    drawCone(20.f, 0.05 * scale, 0.1 * scale);
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
