#pragma once

#include "maths.hpp"

// Utils to draw with OpenGL
namespace gl
{
    void drawTriangle      (const float&    size, const GLuint& texture = 0);                             // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawQuad          (const float&    size, const GLuint& texture = 0);                             // Draw quad centered (halfSize = 0.5)
    void drawDividedQuad   (const float&    size, const GLuint& texture = 0, bool negateNormals = false); // Draw a quad with 2 triangles.
    void drawDividedQuad   (const vector2f& size, const GLuint& texture = 0, bool negateNormals = false); // Draw a quad with 2 triangles.
    void drawCube          (const float&    size, const GLuint& texture = 0);                             // Draw a cube.
    void drawSubdividedCube(const int& resX, const int& resY, const int& resZ, const float& size);        // Draw a cube (res = number of subdivision on each axes)

    void drawSphere      (const int& lon, const int& lat, const float& r);       // Draw sphere (longitudes, lattitudes)
    void drawPointSphere (const int& lon, const int& lat, const float& r);       // Draw a sphere with points
    void drawHelperSphere(const float& r, const float& theta, const float& phi); // Draw a helper sphere.

    void drawCone(const int& res, const float& r, const float& h); // Draw cone primitive (res = )
    void drawGizmo(const float& scale);                            // Draw gizmo (3 axes from 0.0 to 1.0 of different color)
}