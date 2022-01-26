#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "gl.hpp"
#include "draw.hpp"
#include "maths.hpp"

// Class for an interactable object.
class Interactable
{
private:
    bool     active = true;                // Dictates if the object can be interacted with.
    GLint    interactionKey;               // The key that should be used to interact with the object.
    float    interationDist = 15;          // The distance at which the object can be interacted with.
    vector3f pos;                          // The position of the interactable object.

public:
    // Constructor/Destructor.
    Interactable();
    Interactable(const vector3f& _pos, const GLint& _interactionKey, const float& _interactionDist = 15);
    ~Interactable() {}

    // Returns true if the object is interacted with.
    bool interaction(GLFWwindow* window, const vector3f& cameraPos);

    // ---- Setters ---- //
    void setActive(const bool& _active);
    void setPos(const vector3f& _pos);
};