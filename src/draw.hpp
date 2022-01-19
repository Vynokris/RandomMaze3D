#pragma once

// Utils to draw with OpenGL
namespace gl
{
    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawTriangle(float size, GLuint texture);
    // Draw quad centered (halfSize = 0.5)
    void drawQuad(float size, GLuint texture);
    // Draw a cube (res = number of subdivision on each axes)
    void drawCube(int resX, int resY, int resZ, float size);
    // Draw sphere (longitudes, lattitudes)
    void drawSphere(int lon, int lat, float r);
    // Draw a sphere with points
    void drawPointSphere(int lon, int lat, float r);
    // Draw a helper sphere.
    void drawHelperSphere(float r, float theta, float phi);
    // Draw cone primitive (res = )
    void drawCone(int res, float r, float h);
    // Draw gizmo (3 axes from 0.0 to 1.0 of different color)
    void drawGizmo(float scale);
}