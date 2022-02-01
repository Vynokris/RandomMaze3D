#include "minimap.hpp"
#include "draw.hpp"
#include "bmpLoader.hpp"
#include <cmath>
#include <cstdio>
#include <ctime>

// Note: I don't know how demanding it is to reload a texture at runtime.
//       I looked it up quickly but didn't find definitive answers.
//       I do it everytime the player changes tiles, but I didn't see much of an impact on the fps since our PCs are beasts.

Minimap::Minimap(const int& _tileSize)
{
    tileSize    = _tileSize;

    // Load the minimap's texture data and texture.
    textureData = loadBmpData("art/map.bmp", textureSize[0], textureSize[1], padding);
    texture     = loadTextureFromData(textureData, textureSize[0], textureSize[1], 0, false);
}

Minimap::~Minimap()
{
    delete[] textureData;
}

void Minimap::updateCurrentTile(const vector3f& cameraPos, const vector2i& startTile)
{
    vector2i tilePos = { (int)(cameraPos.x + startTile.x * tileSize + tileSize/2) / tileSize, 
                         (int)(cameraPos.z + startTile.y * tileSize)              / tileSize };

    static vector2i lastTilePos = { -1, -1 };

    // Get the offset to the start of the maze texture.
    int textureStartOffset = (5 * textureSize[0] + 5) * 3;

    // If the player changed tile, reset the last tile color.
    if (lastTilePos != tilePos)
    {
        // Get the pixel offset at the end of each line.
        int textureWidthOffset[2] = { (lastTilePos.y+2) * padding ,
                                      (tilePos.y    +2) * padding };

        // Compute the offset to the current pixel in the minimap texture.
        int tilePosInTexture[2] = { textureStartOffset + (lastTilePos.y * textureSize[0] + lastTilePos.x) * 3 + textureWidthOffset[0], 
                                    textureStartOffset + (tilePos.y     * textureSize[0] + tilePos.x)     * 3 + textureWidthOffset[1] };

        // Change the last tile color.
        if (lastTilePos != vector2i{ -1, -1 })
        {
            textureData[tilePosInTexture[0]]     = 108;
            textureData[tilePosInTexture[0] + 1] = 135;
            textureData[tilePosInTexture[0] + 2] = 153;
        }

        // Change the player tile color.
        textureData[tilePosInTexture[1]]     = 255;
        textureData[tilePosInTexture[1] + 1] = 210;
        textureData[tilePosInTexture[1] + 2] = 70;

        // Update the last tile position.
        lastTilePos = tilePos;

        // Reload the minimap texture.
        loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
    }
}

void Minimap::updateOpenedChests(const vector2i& chestTile)
{
    // Get the offset to the start of the maze texture.
    int textureStartOffset = (5 * textureSize[0] + 5) * 3;

    // Get the pixel offset at the end of each line.
    int textureWidthOffset = (chestTile.y+2) * padding;

    // Compute the offset to the chest pixel in the minimap texture.
    int chestTileInTexture = textureStartOffset + (chestTile.y * textureSize[0] + chestTile.x) * 3 + textureWidthOffset;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            // Change the chest pixel color.
            if (x == 0 && y == 0)
            {
                textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3]     = 70;
                textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3 + 1] = 255;
                textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3 + 2] = 70;
            }
            // Change the surrounding path pixel colors without erasing the player's position.
            else if (textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3] != 255)
            {
                textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3]     = 108;
                textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3 + 1] = 135;
                textureData[chestTileInTexture + y * padding + (y*textureSize[0] + x) * 3 + 2] = 153;
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
            if (maze[y-4][x-4])
            {
                textureData[y * padding + (y*textureSize[0] + x) * 3]     = 108;
                textureData[y * padding + (y*textureSize[0] + x) * 3 + 1] = 135;
                textureData[y * padding + (y*textureSize[0] + x) * 3 + 2] = 153;
            }
        }
    }

    // Reload the minimap texture.
    loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
}

void Minimap::render() const
{
    // Render the minimap very close to the camera, so that it clips with as little objects as possible.
    glPushMatrix();
    glTranslatef(0.0274, -0.0132, -0.02);
    gl::drawDividedQuad(0.01, texture);
    glPopMatrix();
}
