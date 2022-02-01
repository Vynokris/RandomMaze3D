#include "camera.hpp"
#include <GLFW/glfw3.h>


Camera::Camera(GLFWwindow* _window) : window(_window)
{
    glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
}

Camera::Camera(GLFWwindow* _window, const vector3f& _pos, const vector3f& _rot, const float& _speed) : window(_window), speed(_speed), pos(_pos), rot(_rot)
{
    glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
}

void Camera::update()
{
    // WASD, space & shift keys to move the camera.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vector3f lookAtPoint = getSphericalCoords(speed, DEG2RAD*90, DEG2RAD*(360 - rot.x - 90));
        pos.x += lookAtPoint.x; pos.y += lookAtPoint.y; pos.z += lookAtPoint.z;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vector3f lookAtPoint = getSphericalCoords(speed, DEG2RAD*90, DEG2RAD*(360 - rot.x - 90));
        pos.x -= lookAtPoint.x; pos.y -= lookAtPoint.y; pos.z -= lookAtPoint.z;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vector3f lookAtPoint = getSphericalCoords(speed, DEG2RAD*90, DEG2RAD*(360 - rot.x));
        pos.x -= lookAtPoint.x; pos.y -= lookAtPoint.y; pos.z -= lookAtPoint.z;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vector3f lookAtPoint = getSphericalCoords(speed, DEG2RAD*90, DEG2RAD*(360 - rot.x));
        pos.x += lookAtPoint.x; pos.y += lookAtPoint.y; pos.z += lookAtPoint.z;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        pos.y += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        pos.y -= speed;
    }

    // Mouse to rotate the camera on X and Y.
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        vector2double newMousePos;
        glfwGetCursorPos(window, &newMousePos.x, &newMousePos.y);

        rot.x -= (newMousePos.x - mousePos.x) / 7;
        rot.y -= (newMousePos.y - mousePos.y) / 7;
        rot.y  = clamp(rot.y, -90, 90);

        glfwSetCursorPos(window, mousePos.x, mousePos.y);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
    }
}

void Camera::applyTransforms()
{
    // Move the modelview matrix to match the camera position and rotation.
    glRotatef   (-rot.y, 1.f, 0.f, 0.f);
    glRotatef   (-rot.x, 0.f, 1.f, 0.f);
    glRotatef   (-rot.z, 0.f, 0.f, 1.f);
    glTranslatef(-pos.x, -pos.y, -pos.z);
}

vector3f Camera::getPos()
{
    return pos;
}

vector3f Camera::getRot()
{
    return rot;
}

vector3f Camera::getForwardVec()
{
    return getSphericalCoords(1, DEG2RAD*(360 - rot.y + 90), DEG2RAD*(360 - rot.x - 90));
}

void Camera::setPos(const vector3f& coords)
{
    pos = coords;
}

void Camera::setRot(const vector3f& angles)
{
    rot = angles;
}
