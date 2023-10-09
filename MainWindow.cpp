#include "MainWindow.h"
#include "Camera.h"
#include "Renderer.h"

MainWindow* MainWindow::selfWindow = NULL;

MainWindow::MainWindow()
{
    width = height = 0;
    window = NULL;
    cameraPtr = NULL;
    selfWindow = this;
}

bool MainWindow::Init(std::string title, int width, int height, Camera* camera)
{
    this->cameraPtr = camera;
    this->width = width;
    this->height = height;

    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &MainWindow::OnWindowResized);
    glfwSetCursorPosCallback(window, &MainWindow::OnMouseMove);
    glfwSetMouseButtonCallback(window, &MainWindow::OnMouseClick);
    glfwSetScrollCallback(window, &MainWindow::OnMouseScroll);
    glfwSetKeyCallback(window, &MainWindow::OnKey);
 
    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return true;
}

void MainWindow::OnWindowResized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* MainWindow::GetWindow()
{
    return window;
}

void MainWindow::OnMouseMove(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (MainWindow::selfWindow->firstMouse)
    {
        MainWindow::selfWindow->lastX = xpos;
        MainWindow::selfWindow->lastY = ypos;
        MainWindow::selfWindow->firstMouse = false;
    }

    float xoffset = xpos - MainWindow::selfWindow->lastX;
    float yoffset = MainWindow::selfWindow->lastY - ypos; // reversed since y-coordinates go from bottom to top

    MainWindow::selfWindow->lastX = xpos;
    MainWindow::selfWindow->lastY = ypos;

    MainWindow::selfWindow->cameraPtr->ProcessMouseMovement(xoffset, yoffset);
}

void MainWindow::OnMouseClick(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    float xposF = (float)xpos;
    float yposF = (float)ypos;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        MainWindow::selfWindow->cameraPtr->OnLMouseDown(xposF, yposF);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        MainWindow::selfWindow->cameraPtr->OnLMouseUp(xposF, yposF);
    }
}

void MainWindow::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    MainWindow::selfWindow->cameraPtr->ProcessMouseScroll((float)yoffset);
}

void MainWindow::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        Renderer::SwitchWorldViewType();
    }
}

void MainWindow::ProcessInput(float dt)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPtr->ProcessKeyboard(CameraAction::FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPtr->ProcessKeyboard(CameraAction::BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPtr->ProcessKeyboard(CameraAction::LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPtr->ProcessKeyboard(CameraAction::RIGHT, dt);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPtr->ProcessKeyboard(CameraAction::UPWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPtr->ProcessKeyboard(CameraAction::DOWNWARD, dt);

}