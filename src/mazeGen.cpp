#include "mazeGen.hpp"
#include "draw.hpp"
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <ctime>

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
    if (width % 2 == 0)
        width++;
    if (height % 2 == 0)
        height++;

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
        vector2i coords = { rand() % (width - 12) + 6, (height - 1) * i };
        while (maze[(i == 0 ? 1 : height - 2)][coords.x] == 0)
            coords.x = (coords.x + 1) % width;
        makePath(coords);
        (i == 0 ? endTile : startTile) = coords;
    }

    // Set the room coordinates.
    roomCoords[0] = {             2,              2 };
    roomCoords[1] = { (width-1) - 2,              2 };
    roomCoords[2] = {             2, (height-1) - 2 };
    roomCoords[3] = { (width-1) - 2, (height-1) - 2 };
    roomCoords[4] = {  width/2,       height/2      };

    // Create the 5 rooms.
    for (int i = 0; i < 5; i++) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++)
            {
                makePath({ roomCoords[i].x + x, roomCoords[i].y + y });
            }
        }
        // For some reason chests are offset if this isn't done.
        roomCoords[i].y--;
    }

    //! DEBUG: print the maze.
    /*
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%s%d ", (isPath({x, y}) ? "\x1b[32m" : "\x1b[31m"), maze[y][x]);
        }
        printf("\n");
    }
    printf("\x1b[0m");
    */
}

bool MazeGenerator::isInMaze(const vector3f& worldCoords)
{
    vector2i tileCoords = { (int)(worldCoords.x + startTile.x * tileSize + tileSize/2) / tileSize, 
                            (int)(worldCoords.z + height      * tileSize)              / tileSize };

    // Check collisions with chests.
    bool isRoom = false;
    for (int i = 0; i < 5; i++)
        if (tileCoords.x == roomCoords[i].x && tileCoords.y == roomCoords[i].y+1)
            isRoom = true;
    
    // Fix negative collisions (they are broken because of the integer rounding).
    if ((worldCoords.z + height * tileSize) / tileSize < 0)
        isRoom = true;

    return isPath(tileCoords, true) && !isRoom;
}

vector3f MazeGenerator::backToMazeVec(const vector3f& worldCoords)
{
    // Get the coordinates of the tile the player is in.
    vector2i tileCoords = { (int)clamp(roundInt(worldCoords.x + startTile.x * tileSize + tileSize/2) / tileSize, 2, width -2), 
                            (int)clamp(roundInt(worldCoords.z + height      * tileSize)              / tileSize, 1, height-2) };
    
    // Get the nearest path tile to the player.
    vector2i closestPathTile;
    vector2f closestPathWorld;
    double   closestPathDist = -1;
    for (int y = -1; y <= 1; y++) 
    {
        for (int x = -1; x <= 1; x++) 
        {
            // Check collisions with chests.
            bool isRoom = false;
            for (int i = 0; i < 5; i++)
                if (tileCoords.x + x == roomCoords[i].x && tileCoords.y + y == roomCoords[i].y)
                    isRoom = true;

            // Check collisions with walls.
            if (isPath({ tileCoords.x + x, tileCoords.y + y }) && !isRoom)
            {
                vector2f curTileWorldCoords = { (float)(tileCoords.x + x - startTile.x) * tileSize, 
                                                (float)(tileCoords.y + y - height)      * tileSize + tileSize/2 };
                double curTileDist = sqrt(sqpow(curTileWorldCoords.x - worldCoords.x) + sqpow(curTileWorldCoords.y - worldCoords.z));

                if (curTileDist < closestPathDist || closestPathDist == -1)
                {
                    closestPathTile  = { tileCoords.x + x, tileCoords.y + y };
                    closestPathWorld = curTileWorldCoords;
                    closestPathDist  = curTileDist;
                }
            }
        }
    }

    // Do some trigonometry to find the length of the vector that goes from the tile to the wall, passing through the player.
    vector2f closestPathToPos = vector2fFromPoints(closestPathWorld, { worldCoords.x, worldCoords.z });
    float    angle            = std::abs((vector2fAngle(closestPathToPos) + PI/4) - (PI/2) * floor((vector2fAngle(closestPathToPos) + PI/4) / (PI/2)) - PI/4);
    float    distance         = (tileSize / 2) / cos(angle) - 0.07;

    // Find the vector that brings the player back in bounds.
    vector2f backToMazeVector = vector2fFromPoints({ worldCoords.x, worldCoords.z }, closestPathWorld);
             backToMazeVector = { backToMazeVector.x + vector2fNormalize(closestPathToPos).x * distance, backToMazeVector.y + vector2fNormalize(closestPathToPos).y * distance };

    return { backToMazeVector.x, 0, backToMazeVector.y };
}

void MazeGenerator::render(std::map<std::string, GLuint>& textures, const bool& allChestsOpened)
{
    // Set a constant seed to have consistant random textures across all game frames.
    srand(0);

    // I use this to determine which texture to use.
    int randTexture;
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
                    // Rotate to place each face in the right place.
                    glRotatef(90, 0, 1, 0);
                    glTranslatef(tileSize/2, 0, tileSize/2);

                    // Don't draw the 
                    if (endTile.x == x && endTile.y == y)
                        neighboors[1] = { x, y };

                    if (!isPath(neighboors[i], true))
                    {
                        // Render the lower part of the wall with a random texture.
                        randTexture = rand() % 5;
                        gl::drawDividedQuad(tileSize, textures[("wall" + std::to_string(randTexture < 1 ? 1 : 0)).c_str()]);
                        glTranslatef(0, tileSize, 0);

                        // Render the higher part of the wall with a random texture.
                        randTexture = rand() % 5;
                        gl::drawDividedQuad(tileSize, textures[("wall" + std::to_string(randTexture < 1 ? 1 : 0)).c_str()]);
                        glTranslatef(0, -tileSize, 0);
                    }
                }

                // Render the upper face with a random texture.
                randTexture = rand() % 5;
                glRotatef(-90, 1, 0, 0);
                glTranslatef(0, tileSize/2, tileSize*1.5);
                gl::drawDividedQuad(tileSize, textures[("ceiling" + std::to_string(randTexture < 1 ? 1 : 0)).c_str()]);

                // Render the lower face.
                glRotatef(180, 1, 0, 0);
                glTranslatef(0, 0, tileSize*2);
                gl::drawDividedQuad(tileSize, textures["floor"]);
            }

            glPopMatrix();
        }
    }

    // Reset the seed.
    srand(time(NULL));

    // Render the start door.
    glPushMatrix();
    glTranslatef(0, 0, -0.05);
    gl::drawDividedQuad(tileSize, textures["door0"]);
    glTranslatef(0, 10, 0);
    gl::drawDividedQuad(tileSize, textures["door1"]);
    glPopMatrix();

    // Render the end door.
    glPushMatrix();
    glTranslatef((endTile.x - startTile.x) * tileSize, 0, (endTile.y - startTile.y) * tileSize - tileSize);
    glTranslatef(0, 0, 0.05);
    if (allChestsOpened) {
        glRotatef(-90, 0, 1, 0);
        glTranslatef(tileSize/2, 0, tileSize/2 - 0.05);
    }
    gl::drawDividedQuad(tileSize, textures["door0"]);
    glTranslatef(0, 10, 0);
    gl::drawDividedQuad(tileSize, textures["door1"]);
    glPopMatrix();

    // Render the room chests.
    for (int i = 0; i < 5; i++)
    {
        // Get the world position of the current room.
        vector2f roomPos = { (float)(roomCoords[i].x - startTile.x) * tileSize, 
                             (float)(roomCoords[i].y - startTile.y) * tileSize + tileSize/2, };

        // Draw the light texture.
        glPushMatrix();
        glTranslatef(roomPos.x, 14.95, roomPos.y);
        glRotatef(-90, 1, 0, 0);
        gl::drawDividedQuad(10, textures["light"]);
        glPopMatrix();

        // Draw the chest.
        glPushMatrix();
        glTranslatef(roomPos.x, 0, roomPos.y);
        glTranslatef(0, 0, tileSize/2);

        // Render the 4 side faces.
        for (int i = 0; i < 4; i++)
        {
            glRotatef(-90, 0, 1, 0);
            glTranslatef(-tileSize/2, 0, tileSize/2);
            if (i == 3)
                gl::drawDividedQuad(tileSize, textures["chest1"], true);
            else
                gl::drawDividedQuad(tileSize, textures["chest0"], true);
        }

        // Render the upper and lower faces.
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, -tileSize/2, -tileSize/2);
        gl::drawDividedQuad(tileSize, textures["chest2"], true);
        glTranslatef(0, 0, tileSize);
        glPopMatrix();
    }
}

vector2i MazeGenerator::getMazeStart()       const { return startTile; }

vector2i MazeGenerator::getMazeEnd()         const { return endTile; }

vector2i MazeGenerator::getRoomCoords(int i) const { return roomCoords[i]; } 
