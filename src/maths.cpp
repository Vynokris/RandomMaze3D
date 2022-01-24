#include "maths.hpp"

#include <cmath>


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
