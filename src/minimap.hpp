#pragma once

#include <vector>
#include "gl.hpp"
#include "maths.hpp"

class Minimap
{
private:
    unsigned char* textureData;    // The minimap texture's pixel data.
    GLuint         texture;        // The minimap texture.
    int32_t        textureSize[2]; // The minimap texture's size.
    int            padding;        // The offset in width due to the texture not being multiple of 2.
    int            tileSize;       // The size of each maze tile.

public:
    Minimap(const int& _tileSize);
    ~Minimap();

    // Updates the map with the current tile the player is in.
    void updateCurrentTile (const vector3f& cameraPos, const vector2i& startTile);

    // Reveals a whole room whenever the player opens a chest.
    void updateOpenedChests(const vector2i& chestTile);

    // Shows all of the paths of the maze on the map.
    void showAllPaths      (const std::vector<std::vector<int>>& maze);

    // Renders the map on the player's hud.
    void render() const;
};