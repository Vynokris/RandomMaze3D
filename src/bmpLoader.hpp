#pragma once

#include "gl.hpp"
#include <cstdint>

#pragma pack(push, 1)
struct BmpHeader
{
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t sizeOfBitmap;
    int32_t  horizontalResolution;
    int32_t  verticalResolution;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

unsigned char* loadBmpData(const char* filename, int32_t& widthGetter, int32_t& heightGetter, int32_t& xOffsetGetter);

GLuint loadTextureFromData(unsigned char* data, const int32_t& width, const int32_t& height, GLuint texture = 0, const bool& deleteData = true);

GLuint loadBmpTexture(const char* filename);

GLuint loadTestTexture();
