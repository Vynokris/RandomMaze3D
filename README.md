# Introduction to OpenGL

## General Infromation

The end goal was to create a maze which the player could explore. It had to be textured, lit and could optionally have collisions. <br> 
<br>
The player is positionned at the start of a randomly generated and textured maze. <br> 
He must explore it to find the 5 rooms where chests need to be opened. <br> 
Once all chests have been opened, the exit door will open and the player will be able to exit the maze. <br>
When this happens, collisions are disabled, all of the paths are revealed on the minimap, and a bright light is turned on. <br>

<br>


## Build and launch

Use the make command to build the project and start the "maze" executable to launch it.

<br>

## Camera controls

Use WASD to move the camera in the world.                                       <br>
Right click and move the mouse to rotate the camera.                            <br>
Space and shift can be used to move up and down.                                <br>
Use the 1 and 2 keys to toggle wireframe view.                                  <br>
Use the 3 and 4 keys to switch between perspective and orthographic views.      <br>
Use the 5 and 6 keys to toggle a bright ambient light.                          <br>
Use the 7 and 8 keys to toggle the player's point light.                        <br>
Use the 9 and 0 keys to toggle collisions with the maze.                        <br>
Use the numpad numbers and decimal point to test the rendering of basic shapes. <br>
(for some reason GL_COLOR_MATERIAL makes the lights brighter, and the only fix is to restart the program)

<br>

## Codebase overview

### draw.hpp defines functions to draw shapes:
- Textured triangles
- Textured quads
- Textured quads divided in two triangles
- Textured cubes (with divided quad textures)
- Subdivided cubes (with each subdivision being a quad divided into two triangles)
- Spheres
- Spheres made of points
- Cones
- Gizmos

<br>

### camera.hpp defines:
- a camera class
- a function to update the camera position according to player input
- a funtions to apply the camera's transformations to the modelview matrix

<br>

### bmpLoader.hpp defines:
- a function to load an OpenGL texture from a bmp file
- a function to load the data from a bmp file as an array of pixels
- a function to load an OpenGl texture from an array of pixels

<br>

### lights.hpp defines:
- a function to setup all of the lights of the scene
- a function to update all of the positions of the lights

<br>

### mazeGen.hpp defines:
- a maze generator class
- a function to generate a maze of given size
- a function to render the generated maze
- a function to move the player back inside the maze

<br>

### minimap.hpp defines:
- a minimap class
- a function to update the minimap according to the player's position
- a function to update the minimap when a chest is opened
- a function to show all of the paths of the maze on the minimap
- a function to render the minimap on the player's hud

<br>

### interactable.hpp defines:
- an interactable object class
- this creates a position at which the player can press a key to interact with the object
- the interaction function returns true when the player interacts with the object
