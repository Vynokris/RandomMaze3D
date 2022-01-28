#include "minimap.hpp"
#include "draw.hpp"
#include "bmpLoader.hpp"
#include <cmath>
#include <cstdio>

Minimap::Minimap(int& mazeWidth, int& mazeHeight, const int& _tileSize)
{
    tileSize    = _tileSize;

    // Load the minimap's texture data and texture.
    textureData = loadBmpData("art/map.bmp", textureSize[0], textureSize[1], xOffset);
    texture     = loadTextureFromData(textureData, textureSize[0], textureSize[1], 0, false);

    // Make sure the maze height and width are not even.
    if (mazeWidth % 2 == 0)
        mazeWidth++;
    if (mazeHeight % 2 == 0)
        mazeHeight++;

    // Initialize the visitedTiles array to 0s.
    visitedTiles.assign(mazeHeight, std::vector<bool>());
    for (int i = 0; i < mazeHeight; i++)
        visitedTiles[i].assign(mazeWidth, false);
}

Minimap::~Minimap()
{
    delete[] textureData;
}

void Minimap::updateVisitedTiles(const vector3f& cameraPos, const vector2i& startTile)
{
    vector2i tilePos = { (int)(cameraPos.x + startTile.x * tileSize + tileSize/2) / tileSize, 
                         (int)(cameraPos.z + startTile.y * tileSize)              / tileSize };
    
    if (!visitedTiles[tilePos.y][tilePos.x])
    {
        visitedTiles[tilePos.y][tilePos.x] = true;

        // Get the offset to the start of the maze texture.
        int textureStartOffset = (5 * textureSize[0] + 5) * 3;

        // Get the pixel offset at the end of each line.
        int textureWidthOffset = (tilePos.y+2) * xOffset;

        // Compute the offset to the current pixel in the minimap texture.
        int tilePosInTexture = textureStartOffset + (tilePos.y * textureSize[0] + tilePos.x) * 3 + textureWidthOffset;

        // Change the pixel color.
        textureData[tilePosInTexture]     = 108;
        textureData[tilePosInTexture + 1] = 135;
        textureData[tilePosInTexture + 2] = 153;

        // Reload the minimap texture.
        loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
    }
}

void Minimap::updateOpenedChests(const vector2i& chestTile)
{
    visitedTiles[chestTile.y][chestTile.x] = true;

    // Get the offset to the start of the maze texture.
    int textureStartOffset = (5 * textureSize[0] + 5) * 3;

    // Get the pixel offset at the end of each line.
    int textureWidthOffset = (chestTile.y+2) * xOffset;

    // Compute the offset to the chest pixel in the minimap texture.
    int chestTileInTexture = textureStartOffset + (chestTile.y * textureSize[0] + chestTile.x) * 3 + textureWidthOffset;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            // Change the chest pixel color.
            if (x == 0 && y == 0)
            {
                textureData[chestTileInTexture + y * xOffset + (y*textureSize[0] + x) * 3]     = 69;
                textureData[chestTileInTexture + y * xOffset + (y*textureSize[0] + x) * 3 + 1] = 150;
                textureData[chestTileInTexture + y * xOffset + (y*textureSize[0] + x) * 3 + 2] = 90;
            }
            // Change the surrounding path pixel colors.
            else
            {
                textureData[chestTileInTexture + y * xOffset + (y*textureSize[0] + x) * 3]     = 108;
                textureData[chestTileInTexture + y * xOffset + (y*textureSize[0] + x) * 3 + 1] = 135;
                textureData[chestTileInTexture + y * xOffset + (y*textureSize[0] + x) * 3 + 2] = 153;
            }
        }
    }

    // Reload the minimap texture.
    loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
}

void Minimap::showAllPaths(const std::vector<std::vector<int>>& maze)
{
    // Loop over the whole maze texture.
    for (int y = 4; y-4 < (int)maze.size(); y++)
    {
        for (int x = 4; x-4 < (int)maze[0].size(); x++)
        {
            // Change the color of path pixels.
            if (maze[y-4][x-4] && !visitedTiles[y-4][x-4])
            {
                textureData[y * xOffset + (y*textureSize[0] + x) * 3]     = 108;
                textureData[y * xOffset + (y*textureSize[0] + x) * 3 + 1] = 135;
                textureData[y * xOffset + (y*textureSize[0] + x) * 3 + 2] = 153;
            }
        }
    }

    // Reload the minimap texture.
    loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
}

void Minimap::render()
{
    glPushMatrix();
    glTranslatef(0.0274, -0.0132, -0.02);
    gl::drawDividedQuad(0.01, texture);
    glPopMatrix();
}
