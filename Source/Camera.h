#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum struct CameraAction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

// Default camera values
const float SCR_WIDTH = 800.0f;
const float SCR_HEIGHT = 600.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 rotation);
    
    //updates vectors and matrices
    void Update();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CameraAction direction, float deltaTime);
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    //get left mouse btn events
    void OnLMouseDown(float x, float y);
    void OnLMouseUp(float x, float y);

    const glm::mat4& GetViewMatrix();
    const glm::mat4& GetProjectionMatrix();
    const glm::mat4& GetOrthoMatrix();
private:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler Angles
    float yaw;
    float pitch;
    float roll;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    //Matrices
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 orthoMatrix;

    //allow rotate camera around
    bool rotatable;
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateCameraVectors();

    // calculates the camera Matrices, view, projection
    void UpdateMatrices();
};
