#include "bmpLoader.hpp"

#include <cstdio>
#include <cmath>

unsigned char* loadBmpData(const char* filename, int32_t* widthGetter, int32_t* heightGetter)
{
    // Create the texture and the bmp header object.
    GLuint texture;
    BmpHeader bmpHeader;

    // Open the texture file.
    FILE* f;
    f = fopen(filename, "rb");
    if (f == NULL) return 0;

    // Read the file metadata.
    fread(&bmpHeader, 54, 1, f);
    if (bmpHeader.fileType != 0x4D42 || bmpHeader.bitsPerPixel != 24)
        return 0;

    // Read the file data and close it.
    unsigned char* data = new unsigned char[bmpHeader.sizeOfBitmap];
    fseek(f, bmpHeader.dataOffset, 0);
    fread(data, bmpHeader.sizeOfBitmap, 1, f);
    fclose(f);

    *widthGetter  = bmpHeader.width;
    *heightGetter = bmpHeader.height;

    return data;
}

GLuint loadTextureFromData(unsigned char* data, const int32_t& width, const int32_t& height, GLuint texture, const bool& deleteData)
{
    // Allocate a new texture and bind it to a 2D target.
    if (texture == 0)
        glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set some texture parameters.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);

    // Add the file data onto the texture and free the data.
    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, abs(width), abs(height), 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (deleteData)
        delete[] data;
    return texture;
}

GLuint loadBmpTexture(const char* filename)
{
    // Create the texture and the bmp header object.
    GLuint texture;
    BmpHeader bmpHeader;

    // Open the texture file.
    FILE* f;
    f = fopen(filename, "rb");
    if (f == NULL) return 0;

    // Read the file metadata.
    fread(&bmpHeader, 54, 1, f);
    if (bmpHeader.fileType != 0x4D42 || bmpHeader.bitsPerPixel != 24)
        return 0;

    // Read the file data and close it.
    unsigned char* data = new unsigned char[bmpHeader.sizeOfBitmap];
    fseek(f, bmpHeader.dataOffset, 0);
    fread(data, bmpHeader.sizeOfBitmap, 1, f);
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
    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, abs(bmpHeader.width), abs(bmpHeader.height), 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] data;
    return texture;
}

GLuint loadTestTexture()
{
    // Create the texture, its width and height, and its data.
    GLuint texture;
    int width  = 2;
    int height = 2;
    unsigned char* data = new unsigned char[width*height*3];

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

    delete[] data;
    return texture;
}
