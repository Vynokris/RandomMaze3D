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

// Get coordinates of a point on a sphere of radius r.
vector3f getSphericalCoords(const float& r, const float& theta, const float& phi);

// Rounds the given value to the nearest int.
int roundInt(double val);

// Rounds down the given value.
int floorInt(double val);

// Rounds up the given value.
int ceilInt(double val);

// Returns the sqare power of the given value.
double sqpow(double val);

// Returns 1 if the given value is positive or null, and -1 if it is negative.
int signOf(double val);
