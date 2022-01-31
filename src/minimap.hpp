#pragma once

#include <vector>
#include "gl.hpp"
#include "maths.hpp"

class Minimap
{
private:
    unsigned char* textureData; // The minimap texture's pixel data.
    GLuint texture;             // The minimap texture.
    int32_t textureSize[2];     // The minimap texture's size.
    int xOffset;                // The offset in width due to the texture not being multiple of 2.
    int tileSize;               // The size of each maze tile.

public:
    Minimap(int& mazeWidth, int& mazeHeight, const int& _tileSize);
    ~Minimap();

    void updateCurrentTile(const vector3f& cameraPos, const vector2i& startTile);
    void updateOpenedChests(const vector2i& chestTile);
    void showAllPaths(const std::vector<std::vector<int>>& maze);
    void render();
};