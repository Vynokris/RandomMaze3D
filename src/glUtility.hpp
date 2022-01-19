#pragma once

#include "gl.hpp"

#define PI 3.14159265358979323846f
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)

struct float2
{
    float x;
    float y;
};

struct float3
{
    float x;
    float y;
    float z;
};

float3 getSphericalCoords(float r, float theta, float phi);

GLuint loadTexture(const char* filename);

GLuint loadTestTexture();
