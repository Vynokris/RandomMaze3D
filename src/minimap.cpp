#include "minimap.hpp"
#include "draw.hpp"
#include "bmpLoader.hpp"
#include <cmath>
#include <cstdio>

Minimap::Minimap(int& mazeWidth, int& mazeHeight, const int& _tileSize)
{
    tileSize    = _tileSize;

    // Load the minimap's texture data and texture.
    textureData = loadBmpData("Resources/Art/map.bmp", &textureSize[0], &textureSize[1]);
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

        int textureStartOffset = (4 * textureSize[0] + 4) * 3;
        int tilePosInTexture   = textureStartOffset + (tilePos.y * textureSize[0] + tilePos.x) * 3;

        textureData[tilePosInTexture]     = 108;
        textureData[tilePosInTexture + 1] = 135;
        textureData[tilePosInTexture + 2] = 153;

        loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
    }
}

void Minimap::updateOpenedChests(const vector2i& chestTile)
{
    visitedTiles[chestTile.y][chestTile.x] = true;

    int textureStartOffset = (4 * textureSize[0] + 4) * 3;
    int chestTileInTexture = textureStartOffset + (chestTile.y * textureSize[0] + chestTile.x) * 3;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (x == 0 && y == 0)
            {
                textureData[chestTileInTexture + (y*textureSize[0] + x) * 3]     = 69;
                textureData[chestTileInTexture + (y*textureSize[0] + x) * 3 + 1] = 150;
                textureData[chestTileInTexture + (y*textureSize[0] + x) * 3 + 2] = 90;
            }
            else
            {
                textureData[chestTileInTexture + (y*textureSize[0] + x) * 3]     = 108;
                textureData[chestTileInTexture + (y*textureSize[0] + x) * 3 + 1] = 135;
                textureData[chestTileInTexture + (y*textureSize[0] + x) * 3 + 2] = 153;
            }
        }
    }

    loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
}

void Minimap::showAllPaths(const std::vector<std::vector<int>>& maze)
{
    for (int y = 3; y < abs(textureSize[1]) - 5; y++)
    {
        for (int x = 4; x < textureSize[0] - 4; x++)
        {
            if (maze[y-3][x-4] && !visitedTiles[y-3][x-4])
            {
                visitedTiles[y-3][x-4] = true;
                textureData[(y*textureSize[0] + x) * 3]     = 108;
                textureData[(y*textureSize[0] + x) * 3 + 1] = 135;
                textureData[(y*textureSize[0] + x) * 3 + 2] = 153;
            }
        }
    }

    loadTextureFromData(textureData, textureSize[0], textureSize[1], texture, false);
}

void Minimap::render()
{
    glPushMatrix();
    glTranslatef(0.0274, -0.0132, -0.02);
    gl::drawDividedQuad(0.01, texture);
    glPopMatrix();
}
