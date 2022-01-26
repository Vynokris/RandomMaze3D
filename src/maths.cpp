#include "maths.hpp"

#include <cmath>
#include <cassert>
using namespace std;


// Get coordinates of a point on a sphere of radius r.
vector3f getSphericalCoords(const float& r, const float& theta, const float& phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}

// Rounds the given value to the nearest int.
int roundInt(double val) { return (int)round(val); }

// Rounds down the given value.
int floorInt(double val) { return (int)floor(val); }

// Rounds up the given value.
int ceilInt(double val)  { return (int)ceil(val); }

// Returns the square power of the given value.
double sqpow(double val) { return val * val; }

// Returns 1 if the given value is positive or null, and -1 if it is negative.
int signOf(double val)   { if (val == 0) return 1; return val / abs((int)val); }

// Clamps the given value to be superior or equal to the minimum value and inferior or equal to the maximum value.
double clamp(double val, double min, double max)
{
    assert (min <= max); 
    if (val < min) val = min;
    if (val > max) val = max;
    return val;
}

// Clamps the given value to be inferior or equal to the maximum value.
double clampUnder(double val, double max) { if (val > max) val = max; return val; }

// Clamps the given value to be superior or equal to the minimum value.
double clampAbove(double val, double min) { if (val < min) val = min; return val; }

// Linear interpoation between the given values.
double lerp(double val, double start, double end)
{
    return start + val * (end - start);
}

// Remaps the given value from one range to another.
double remap(double val, double inputStart, double inputEnd, double outputStart, double outputEnd)
{
    return outputStart + (val - inputStart) * (outputEnd - outputStart) / (inputEnd - inputStart);
}



// Get the angle of a 2D vector.
float vector2fAngle(const vector2f& v)
{
    return (float)copysign(acos((double)vector2fNormalize(v).x), asin((double)vector2fNormalize(v).y));
}

// Create a 2D vector from 2 2D points.
vector2f vector2fFromPoints(const vector2f& p1, const vector2f& p2)
{
    return { p2.x - p1.x, p2.y - p1.y };
}

// Normalize a 2D vector.
vector2f vector2fNormalize(const vector2f& v)
{
    float length = sqrt(sqpow(v.x) + sqpow(v.y));
    return { v.x / length, v.y / length };
}

vector3f vector3fFromPoints(const vector3f& p1, const vector3f& p2)
{
    return { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
}

float vector3fLength(const vector3f& v)
{
    return sqrt(sqpow(v.x) + sqpow(v.y) + sqpow(v.z));
}

// Resize a 3D vector.
vector3f vector3fResize(const vector3f& v, const float& size)
{
    vector3f v2 = vector3fNormalize(v);
    return { v2.x * size, v2.y * size, v2.z * size };
}

// Normalize a 3D vector.
vector3f vector3fNormalize(const vector3f& v)
{
    float length = sqrt(sqpow(v.x) + sqpow(v.y) + sqpow(v.z));
    return { v.x / length, v.y / length, v.z / length };
}

// 3D vector dot product.
float vector3fDot(const vector3f& v1, const vector3f& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Linear interpolation between two 3D points.
vector3f vector3fLerp(const float& val, const vector3f& start, const vector3f& end)
{
    return { start.x + val * (end.x - start.x), 
             start.y + val * (end.y - start.y), 
             start.z + val * (end.z - start.z) };
}
