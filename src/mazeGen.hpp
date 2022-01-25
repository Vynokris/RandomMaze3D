#pragma once

#include <vector>
#include <map>
#include <string>
#include "maths.hpp"

class MazeGenerator
{
private:
    vector2i startTile; // The start of the maze.
    vector2i endTile;   // The end of the maze.

    void makePath(const vector2i& coords);                                 // Makes the element at the given coordinates a path.
    bool isPath  (const vector2i& coords, const bool& outerWalls = false); // Checks if the element at the given coordinates is a path. If outerWalls is true, coordinates outside of the maze will be walls.
    std::vector<vector2i> nonPathNeighboors (const vector2i& coords);      // Returns all the neighbors of the given element that are not paths.
    vector2i middle(const vector2i& coords1, const vector2i& coords2);     // Returns the coordinates of the element that is between the two given coordinates.
    vector2i choice(const std::vector<vector2i>& array);                   // Returns a random element in the given array.

public:
    int width    = 15; // The width  of the maze.
    int height   = 15; // The height of the maze.
    int tileSize = 10; // The size of each maze tile.
    std::vector<std::vector<int>> maze; // 2D array that represents the maze's data.

    // Constructors.
    MazeGenerator() {}
    MazeGenerator(const int& new_width, const int& new_height) : width(new_width), height(new_height) {}

    // Destructor.
    ~MazeGenerator() {};

    // Generate the maze.
    void generate();

    // Check if the given coordinates are in the maze walls.
    bool isInMaze(vector3f worldCoords);

    // Returns the smallest vector that moves the player in the maze.
    vector3f backToMazeVec(vector3f worldCoords);

    // Render the maze.
    void render(std::map<std::string, GLuint>& textures);

    // Get the maze startint position.
    vector2i getMazeStart();
    // Get the maze ending position.
    vector2i getMazeEnd();
};