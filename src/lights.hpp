#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "gl.hpp"

// Forward declaration of the camera and maze generator classes.
class MazeGenerator;

void setupLights();

void updateLights(GLFWwindow* window, const MazeGenerator& mazeGen, const GLuint& lightTexture);

void updateLightColor(const int& lightID);