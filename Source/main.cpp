// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Include components
#include "MainWindow.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"

//include shapes
#include "Shapes/Shape.h"

#define RGBA(r,g,b,a) glm::vec4(r/255.0f,g/255.0f, b/255.0f, a)

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Function that will create a pencil
void CreatePencil(Shader* mainShader, const glm::vec3& position, const glm::vec3& rotation)
{
    //Create a pencil
    {
        //base
        CylinderShape* base = Shape<CylinderShape>::Create(mainShader, position,
            rotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(46, 47, 41, 1.0f), 3.0f, 0.1f, 0.1);
        base->AttachTexture("Textures/pencilBody.png");
        Renderer::AddToScene(base);


        //Lead
        CylinderShape* leadBody = Shape<CylinderShape>::Create(mainShader, position,
            rotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(249, 241, 221, 1.0f), 0.5f, 0.05f, 0.1f);
        leadBody->SetLocalOffset(glm::vec3(0.0f, -1.75f, 0.0f));
        leadBody->AttachTexture("Textures/wood.jpg");
        Renderer::AddToScene(leadBody);

        CylinderShape* lead = Shape<CylinderShape>::Create(mainShader, position,
            rotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(82, 80, 73, 1.0f), 0.2f, 0.0f, 0.05f);
        lead->SetLocalOffset(leadBody->GetLocalOffset() + glm::vec3(0.0f, -0.35f, 0.0f));
        Renderer::AddToScene(lead);


        //Cap
        CylinderShape* capBody = Shape<CylinderShape>::Create(mainShader, position,
            rotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(157, 136, 98, 1.0f), 0.4f, 0.1f, 0.1f);
        capBody->SetLocalOffset(glm::vec3(0.0f, 1.7f, 0.0f));
        capBody->AttachTexture("Textures/pencilCap.png");
        Renderer::AddToScene(capBody);

        CylinderShape* cap = Shape<CylinderShape>::Create(mainShader, position,
            rotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(200, 200, 200, 1.0f), 0.2f, 0.1f, 0.1f);
        cap->SetLocalOffset(capBody->GetLocalOffset() + glm::vec3(0.0f, 0.3f, 0.0f));
        Renderer::AddToScene(cap);
    }
}

int main(int argc, char* argv[])
{
    //Create camera
    Camera camera(glm::vec3(12.8f, 14.1f, 1.3f), glm::vec3(-52.0f, -177.0f, 0.0f));

    //Create window
    MainWindow mainWindow;
    if (!mainWindow.Init("Stanislav Kovalchuk - Final Project", 800, 600, &camera))
        return EXIT_FAILURE;

    //Init default shape shader
    Shader* mainShader = new Shader("shaders/shape.vs", "shaders/shape.fs");


    //Init renderer
    Renderer::Init(&camera);

    /*Create shapes*/

    //Create plane
    PlaneShape* plane = Shape<PlaneShape>::Create(mainShader, glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 1.0f, 20.0f));
    plane->AttachTexture("Textures/table.png");
    Renderer::AddToScene(plane);

    //Create 2 pencils
    {
        //pencil 1
        CreatePencil(mainShader, glm::vec3(3.0f, 0.3f, 3.0f), glm::vec3(0.0f, 30.0f, -90.0f));

        //pencil 2
        CreatePencil(mainShader, glm::vec3(4.0f, 0.3f, 4.0f), glm::vec3(0.0f, 15.0f, 90.0f));
    }


    //Create notepad
    {
        CubeShape* woodenBase = Shape<CubeShape>::Create(mainShader, glm::vec3(0.0f, 0.3f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 0.05f, 3.0f), RGBA(255, 0, 0, 1.0f));
        woodenBase->AttachTexture("Textures/paper2.jpg");
        Renderer::AddToScene(woodenBase);

        CubeShape* notepad = Shape<CubeShape>::Create(mainShader, glm::vec3(0.5f, 0.35f, -1.0f),
            glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(5.0f, 0.05f, 3.0f), RGBA(255, 0, 0, 1.0f));
        notepad->AttachTexture("Textures/paper.jpg");
        Renderer::AddToScene(notepad);
    }

    //Create a pen
    {
        glm::vec3 penPosition = glm::vec3(3.0f, 0.3f, -4.0f), penRotation = glm::vec3(0.0f, -30.0f, -90.0f);
        //base
        CylinderShape* base = Shape<CylinderShape>::Create(mainShader, penPosition,
            penRotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(46, 47, 41, 1.0f), 3.0f, 0.1f, 0.1);
        base->AttachTexture("Textures/pencilBody.png");
        Renderer::AddToScene(base);


        //Lead
        CylinderShape* leadBody = Shape<CylinderShape>::Create(mainShader, penPosition,
            penRotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(249, 241, 221, 1.0f), 0.5f, 0.05f, 0.1f);
        leadBody->SetLocalOffset(glm::vec3(0.0f, -1.75f, 0.0f));
        leadBody->AttachTexture("Textures/wood.jpg");
        Renderer::AddToScene(leadBody);

        CylinderShape* lead = Shape<CylinderShape>::Create(mainShader, penPosition,
            penRotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(82, 80, 73, 1.0f), 0.2f, 0.0f, 0.05f);
        lead->SetLocalOffset(leadBody->GetLocalOffset() + glm::vec3(0.0f, -0.35f, 0.0f));
        Renderer::AddToScene(lead);

        //Create pens cap
        {
            glm::vec3 offsetFromPen = glm::vec3(-0.5f, 0.0f, -1.5f), capRotation = glm::vec3(0.0f, -55.0f, -90.0f);
            //cap
            CylinderShape* base = Shape<CylinderShape>::Create(mainShader, penPosition + offsetFromPen,
                capRotation, glm::vec3(1.0f, 1.0f, 1.0f), RGBA(46, 47, 41, 1.0f), 0.6f, 0.1f, 0.1);
            base->AttachTexture("Textures/pencilBody.png");
            Renderer::AddToScene(base);
        }
    }

    //Create keyboard
    {
        CubeShape* keyboard = Shape<CubeShape>::Create(mainShader, glm::vec3(-5.0f, 0.3f, 0.0f),
            glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(10.0f, 0.1f, 3.0f), RGBA(255, 0, 0, 1.0f));
        keyboard->AttachTexture("Textures/keyboard.jpg");
        Renderer::AddToScene(keyboard);

    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(mainWindow.GetWindow()))
    {
        // calc delta time
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // update camera matrices
        camera.Update();

        // input
        mainWindow.ProcessInput(deltaTime);

        // Render scene
        Renderer::Render();

        glfwSwapBuffers(mainWindow.GetWindow());    // Flips the the back buffer with the front buffer every frame.
        glfwPollEvents();
    }

    // clear 
    Renderer::Destroy();
    delete mainShader;

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


