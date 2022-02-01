#pragma once

#include "maths.hpp"
class GLFWwindow;

// Utils to draw with OpenGL
namespace gl
{
    void drawTriangle      (const float& size, const GLuint& texture = 0);                                    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawQuad          (const float& size, const GLuint& texture = 0);                                    // Draw quad centered (halfSize = 0.5)
    void drawDividedQuad   (const float& size, const GLuint& texture = 0, const bool& negateNormals = false); // Draw a quad with 2 triangles.
    void drawCube          (const float& size, const GLuint& texture = 0);                                    // Draw a cube.
    void drawSubdividedCube(const float& size, const int& resX, const int& resY, const int& resZ);            // Draw a cube (res = number of subdivision on each axes)

    void drawSphere      (const float& r, const int& lon, const int& lat);       // Draw sphere (longitudes, lattitudes)
    void drawPointSphere (const float& r, const int& lon, const int& lat);       // Draw a sphere with points
    void drawHelperSphere(const float& r, const float& theta, const float& phi); // Draw a helper sphere.

    void drawCone(const float& r, const float& h, const int& res); // Draw cone primitive (res = )
    void drawGizmo(const float& scale);                            // Draw gizmo (3 axes from 0.0 to 1.0 of different color)


    // Draw a shape depending on the pressed keys.
    void testDrawShape(GLFWwindow* window, const vector3f& rotation, const GLint& texture = 0);
}