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

    bool     operator==(const vector2i& v) { return x == v.x && y == v.y; }
    bool     operator!=(const vector2i& v) { return x != v.x || y != v.y; }
    vector2i operator= (const vector2i& v) { x = v.x; y = v.y; return {x, y}; }
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

// Clamps the given value to be superior or equal to the minimum value and inferior or equal to the maximum value.
double clamp(double val, double min, double max);

// Clamps the given value to be inferior or equal to the maximum value.
double clampUnder(double val, double max);

// Clamps the given value to be superior or equal to the minimum value.
double clampAbove(double val, double min);

// Linear interpoation between the given values.
double lerp(double val, double start, double end);

// Remaps the given value from one range to another.
double remap(double val, double inputStart, double inputEnd, double outputStart, double outputEnd);

// Returns true if the given number is a power of 2.
bool isPowOf2(int val);

// Returns the closest power of 2 that is inferior or equal to val.
int getPowOf2Under(int val);

// Returns the closest power of 2 that is superior or equal to val.
int getPowOf2Above(int val);




// Get the angle of a 2D vector.
float vector2fAngle(const vector2f& v);

// Create a 2D vector from 2 2D points.
vector2f vector2fFromPoints(const vector2f& p1, const vector2f& p2);

// Normalize a 2D vector.
vector2f vector2fNormalize(const vector2f& v);

vector3f vector3fFromPoints(const vector3f& p1, const vector3f& p2);

float vector3fLength(const vector3f& v);

// Resize a 3D vector.
vector3f vector3fResize(const vector3f& v, const float& size);

// Normalize a 3D vector.
vector3f vector3fNormalize(const vector3f& v);

// 3D vector dot product.
float vector3fDot(const vector3f& v1, const vector3f& v2);

// Linear interpolation between two 3D points.
vector3f vector3fLerp(const float& val, const vector3f& start, const vector3f& end);
