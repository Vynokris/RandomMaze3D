#pragma once

#define PI 3.14159265358979323846f
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)

struct float3
{
    float x;
    float y;
    float z;
};

float3 getSphericalCoords(float r, float theta, float phi);

// Utils to draw with OpenGL
namespace gl
{
    // Draw triangle with vertices at (-0.5, -0.5), (0.5, -0.5), (0.0, 0.5)
    void drawTriangle(float size);
    // Draw quad centered (halfSize = 0.5)
    void drawQuad(float size);
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