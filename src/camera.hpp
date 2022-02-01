#pragma once

#include "maths.hpp"
class GLFWwindow;

class Camera
{
private:
    GLFWwindow*   window;                   // Pointer to the window.
    float         speed      = 0.1;         // The camera's speed.
    vector2double mousePos;                 // The mouse position.
    vector3f      pos        = { 0, 0, 0 }; // The camera position.
    vector3f      rot        = { 0, 0, 0 }; // The camera rotation.

public:
    // Constructors.
    Camera(GLFWwindow* _window);
    Camera(GLFWwindow* _window, const vector3f& _pos, const vector3f& _rot, const float& _speed = 0.1);

    // Destructor.
    ~Camera() {}

    // Updates the camera's position and rotation according to input.
    void update();
    
    // Applies the camera's transforms on the modelview.
    void applyTransforms();

    // ---- GETTERS ---- //
    vector3f getPos();
    vector3f getRot();
    vector3f getForwardVec();

    // ---- SETTERS ---- //
    void setPos(const vector3f& coords);
    void setRot(const vector3f& angles);
};