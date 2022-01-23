#include "mazeGen.hpp"
#include "draw.hpp"
#include <algorithm>
#include <cstdio>

void MazeGenerator::makePath(const vector2i& coords)
{
    maze[coords.y][coords.x] = 1;
}

bool MazeGenerator::isPath(const vector2i& coords, const bool& outerWalls)
{
    if (coords.x <  0      || coords.y <  0   || 
        coords.y >= height || coords.x >= width)
        return !outerWalls;
    return maze[coords.y][coords.x] == 1;
}

std::vector<vector2i> MazeGenerator::nonPathNeighboors(const vector2i& coords)
{
    std::vector<vector2i> neighboors;

    if (!isPath({ coords.x-2, coords.y }))
        neighboors.push_back({ coords.x-2, coords.y });

    if (!isPath({ coords.x+2, coords.y }))
        neighboors.push_back({ coords.x+2, coords.y });

    if (!isPath({ coords.x, coords.y-2 }))
        neighboors.push_back({ coords.x, coords.y-2 });

    if (!isPath({ coords.x, coords.y+2 }))
        neighboors.push_back({ coords.x, coords.y+2 });

    return neighboors;
}

vector2i MazeGenerator::middle(const vector2i& coords1, const vector2i& coords2)
{
    return { (coords1.x + coords2.x) / 2, (coords1.y + coords2.y) / 2 };
}

vector2i MazeGenerator::choice(const std::vector<vector2i>& array)
{
    return array[rand()%array.size()];
}





void MazeGenerator::generate()
{
    // Make sure the maze height and width are not even.
    if (width % 2 == 0 || height % 2 == 0)
        return;

    // Wipe the maze array.
    maze.assign(height, std::vector<int>());
    for (int i = 0; i < height; i++)
        maze[i].assign(width, 0);

    // Generate the maze.
    std::vector<vector2i> data;
    data.push_back({1, 1});
    makePath({ 1, 1 });
    while (data.size() > 0)
    {
        std::vector<vector2i> neighboors = nonPathNeighboors(data[data.size()-1]);
        if (neighboors.size() <= 0)
        {
            data.pop_back();
        }
        else
        {
            vector2i coord  = choice(neighboors);
            vector2i coord2 = middle(data[data.size()-1], coord);
            makePath(coord);
            makePath(coord2);
            data.push_back(coord);
        }
    }

    // Generate the entrance and exit.
    for (int i = 0; i < 2; i++)
    {
        vector2i coords = { rand() % (width - 2) + 1, (height - 1) * i };
        while (maze[(i == 0 ? 1 : height - 2)][coords.x] == 0)
            coords.x = (coords.x + 1) % width;
        makePath(coords);
        (i == 0 ? endTile : startTile) = coords;
    }
}

bool MazeGenerator::isInMaze(vector3f worldCoords)
{
    vector2i tileCoords = { (int)(worldCoords.x + startTile.x * tileSize + tileSize/2) / tileSize, 
                            (int)(worldCoords.z + height      * tileSize)              / tileSize };
    return isPath(tileCoords, true);
}

void MazeGenerator::render(std::map<std::string, GLuint>& textures)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            glPushMatrix();

            // Translate to the current tile in world coordinates.
            glTranslatef((x - startTile.x) * tileSize, 0, (y - startTile.y) * tileSize);

            if (isPath({ x, y }))
            {
                // Render the walls if the neighboors of the current tile are walls.
                vector2i neighboors[4] = { 
                    { x+1, y   },
                    { x,   y-1 },
                    { x-1, y   },
                    { x,   y+1 },
                };
                for (int i = 0; i < 4; i++)
                {
                    glRotatef(90, 0, 1, 0);
                    glTranslatef(tileSize/2, 0, tileSize/2);
                    if (endTile.x == x && endTile.y == y)
                        neighboors[1] = { x, y };
                    if (!isPath(neighboors[i], true))
                    {
                        gl::drawDividedQuad(tileSize, textures["wall"]);
                        glTranslatef(0, tileSize, 0);
                        gl::drawDividedQuad(tileSize, textures["wall"]);
                        glTranslatef(0, -tileSize, 0);
                    }
                }

                // Render the upper and lower faces.
                glRotatef(90, 1, 0, 0);
                glTranslatef(0, -tileSize/2, -tileSize*1.5);
                gl::drawDividedQuad(tileSize, textures["ceiling"]);
                glTranslatef(0, 0, tileSize*2);
                gl::drawDividedQuad(tileSize, textures["floor"]);
            }

            glPopMatrix();
        }
    }
}
