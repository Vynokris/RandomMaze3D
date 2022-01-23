#pragma once

#include "gl.hpp"
#include <cmath>

#define PI 3.14159265358979323846f
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)


struct vector2i
{
    int x;
    int y;
};

struct vector2f
{
    float x;
    float y;
};

struct vector2double
{
    double x;
    double y;
};

struct vector3f
{
    float x;
    float y;
    float z;
};

vector3f getSphericalCoords(const float& r, const float& theta, const float& phi);