#include "glUtility.hpp"

#include <cmath>
#include <cstdio>


float3 getSphericalCoords(const float& r, const float& theta, const float& phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}

GLuint loadTexture(const char* filename, const int& width, const int& height)
{
    // Create the texture, its width and height, and its data.
    GLuint texture;
    unsigned char data[width*height*3];

    // Open the texture file.
    FILE* f;
    f = fopen(filename, "rb");
    if (f == NULL) return 0;

    // Read the file data and close it.
    fseek(f, 54, 0);
    fread(data, width * height * 3, 1, f);
    fclose(f);

    // Allocate a new texture and bind it to a 2D target.
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set some texture parameters.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);

    // Add the file data onto the texture and free the data.
    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

GLuint loadTestTexture()
{
    // Create the texture, its width and height, and its data.
    GLuint texture;
    int width  = 2;
    int height = 2;
    unsigned char data[width*height*3];

    // Write colors to the texture.
    data[0]  = 255; data[1]  = 0;   data[2]  = 0;
    data[3]  = 0;   data[4]  = 255; data[5]  = 0;
    data[6]  = 0;   data[7]  = 0;   data[8] = 255;
    data[9] = 255;  data[10] = 255; data[11] = 255;

    // Allocate a new texture and bind it to a 2D target.
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set some texture parameters.
    glPixelStoref  (GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);

    // Add the file data onto the texture and free the data.
    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
