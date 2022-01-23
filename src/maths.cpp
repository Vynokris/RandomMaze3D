#include "maths.hpp"

#include <cmath>


vector3f getSphericalCoords(const float& r, const float& theta, const float& phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}
