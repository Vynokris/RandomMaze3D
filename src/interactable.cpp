#include "interactable.hpp"

Interactable::Interactable()
{
    pos = { 0, 0, 0 };
    interactionKey = GLFW_KEY_E;
}

Interactable::Interactable(const vector3f& _pos, const GLint& _interactionKey, const float& _interactionDist)
{
    pos                    = _pos;
    interactionKey         = _interactionKey;
    interationDist         = _interactionDist;
}

bool Interactable::interaction(GLFWwindow* window, const vector3f& cameraPos)
{
    if (active && vector3fLength(vector3fFromPoints(cameraPos, pos)) <= interationDist)
        if (glfwGetKey(window, interactionKey) == GLFW_PRESS)
            return true;

    return false;
}


void Interactable::setActive(const bool& _active)
{
    active = _active;
}

void Interactable::setPos(const vector3f& _pos)
{
    pos = _pos;
}
