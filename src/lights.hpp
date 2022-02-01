#pragma once

class GLFWwindow;
class MazeGenerator;

void setupLights();

void updateLights(GLFWwindow* window, const MazeGenerator& mazeGen, const GLuint& lightTexture);

void updateLightColor(const int& lightID);
