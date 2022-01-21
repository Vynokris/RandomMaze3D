#include "gl.hpp"
#include "glUtility.hpp"
#include "draw.hpp"

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

void gl::drawDividedQuad(const float& size, const GLuint& texture)
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
        
        glTexCoord2f(1, 1); glVertex3f( size/2, -size/2, 0.f);
        glTexCoord2f(1, 0); glVertex3f( size/2,  size/2, 0.f);
        glTexCoord2f(0, 1); glVertex3f(-size/2, -size/2, 0.f);
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
        drawDividedQuad(size, texture);
    }

    // Render the upper and lower faces.
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -size/2, -size/2);
    drawDividedQuad(size, texture);
    glTranslatef(0, 0, size);
    drawDividedQuad(size, texture);

    glPopMatrix();
}

void gl::drawSubdividedCube(const int& resX, const int& resY, const int& resZ, const float& size)
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

void gl::drawSphere(const int& lon, const int& lat, const float& r)
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

void gl::drawPointSphere(const int& lon, const int& lat, const float& r)
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

void gl::drawHelperSphere(const float& r, const float& theta, const float& phi)
{
    glColor3f(1, 1, 1);
    gl::drawPointSphere(20, 20, r);

    glDisable(GL_DEPTH_TEST);
    float3 coords = getSphericalCoords(r, theta, phi);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 1);
    glVertex3f(coords.x, coords.y, coords.z);
    glEnd();
    glEnable(GL_DEPTH_TEST);
}


void gl::drawCone(const int& res, const float& r, const float& h)
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


void gl::drawGizmo(const float& scale)
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
