#include "Camera.h"
#include "GLFW\glfw3.h"

Camera::Camera(glm::vec3 position, glm::vec3 rotation)
    : position(position)
{
    rotatable = false;
    movementSpeed = 20.5f;
    mouseSensitivity = 0.3f;
    zoom = 45.0f;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    pitch = rotation.x;
    yaw = rotation.y;
    roll = rotation.z;
    Update();
}

void Camera::Update()
{
    UpdateCameraVectors();
    UpdateMatrices();
}

void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 frontVec;
    frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVec.y = sin(glm::radians(pitch));
    frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontVec);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}

void Camera::UpdateMatrices()
{
    viewMatrix = glm::lookAt(position, position + front, up);;
    projectionMatrix = glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    float ratio_size_per_depth = atan(glm::radians(zoom / 2.0f)) * 2.0f;
    float distance = glm::length(glm::vec3(0.0f, 0.0f, 0.0f) - position);
    float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;
    float size_y = ratio_size_per_depth * distance;
    float size_x = ratio_size_per_depth * distance * aspect;
    orthoMatrix = glm::ortho(-size_x, size_x, -size_y, size_y, 0.0f, 2.0f * distance);
}

const glm::mat4& Camera::GetViewMatrix()
{
    return viewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix()
{
    return projectionMatrix;
}

const glm::mat4& Camera::GetOrthoMatrix()
{
    return orthoMatrix;
}

void Camera::ProcessKeyboard(CameraAction action, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (action == CameraAction::FORWARD)
        position += front * velocity;
    if (action == CameraAction::BACKWARD)
        position -= front * velocity;
    if (action == CameraAction::LEFT)
        position -= right * velocity;
    if (action == CameraAction::RIGHT)
        position += right * velocity;
    if (action == CameraAction::UPWARD)
        position += up * velocity;
    if (action == CameraAction::DOWNWARD)
        position -= up * velocity;
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    if (!rotatable) return;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    movementSpeed += yoffset;
    movementSpeed = movementSpeed < 1.0f ? 1.0f : movementSpeed;
}

void Camera::OnLMouseDown(float x, float y) {
    rotatable = true;
}

void Camera::OnLMouseUp(float x, float y) {
    rotatable = false;
}