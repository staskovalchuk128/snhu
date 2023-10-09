#pragma once
#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

class Camera;

class MainWindow
{
public:
	MainWindow();

	bool Init(std::string title, int width, int height, Camera* camera);
	void ProcessInput(float dt);
	
	GLFWwindow* GetWindow();
private:
	// Variables for window width and height
	int width, height;
	// Main GLFW window
	GLFWwindow* window;
	bool firstMouse;
	float lastX, lastY;

	Camera* cameraPtr;
	
	static MainWindow* selfWindow;
private:
	static void OnWindowResized(GLFWwindow* window, int width, int height);
	static void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
	static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);
	static void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
};

