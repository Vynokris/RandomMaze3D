#include "glUtility.hpp"

#include <cmath>
#include <cstdio>


float3 getSphericalCoords(float r, float theta, float phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}

GLuint loadTexture(const char* filename)
{
    // Create the texture, its width and height, and its data.
    GLuint texture;
    int width  = 160;
    int height = 160;
    unsigned char* data;
    data = new unsigned char[width*height*3];

    // Open the texture file.
    FILE* f;
    f = fopen(filename, "rb");
    if (f == NULL) return 0;

    // Read the file data and close it.
    fread(data, width * height * 3, 1, f);
    fclose(f);

    // Switch the blue value with the red value, to go from BGR to RGB.
    for(int i = 0; i < width * height ; ++i)
    {
        int index = i*3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];

        data[index] = R;
        data[index+2] = B;
    }

    // Allocate a new texture and bind it to a 2D target.
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Set some texture parameters.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);

    // Add the file data onto the texture and free the data.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(data);

    return texture;
}

GLuint loadTestTexture()
{
    // Create the texture, its width and height, and its data.
    GLuint texture;
    int width  = 2;
    int height = 2;
    unsigned char* data;
    data = new unsigned char[width*height*3+2*height];

    // Write colors to the texture.
    data[0]  = 255; data[1]  = 0;   data[2]  = 0;
    data[3]  = 0;   data[4]  = 255; data[5]  = 0;
    data[8]  = 0;   data[9]  = 0;   data[10] = 255;
    data[11] = 255; data[12] = 255; data[13] = 255;

    // Allocate a new texture and bind it to a 2D target.
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Set some texture parameters.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
    // glPixelStoref(GL_PACK_ROW_LENGTH, width);
    // glPixelStoref(GL_PACK_IMAGE_HEIGHT, height);

    // Add the file data onto the texture and free the data.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(data);

    return texture;
}
