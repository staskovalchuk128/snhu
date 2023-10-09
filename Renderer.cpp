#include "Renderer.h"
#include "RenderableObject.h"
#include "Camera.h"

Camera* Renderer::cameraPtr = NULL;
std::vector<RenderableObject*> Renderer::objectsInScene = {};
WorldViewType Renderer::worldViewType = WorldViewType::PERSPECTIVE;

void Renderer::Init(Camera* cameraPtr)
{
	Renderer::cameraPtr = cameraPtr;
}

void Renderer::Render()
{
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);


	// Clear the frame and z buffers
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get view and projection matrix
	const glm::mat4 projectionMatrix = worldViewType == WorldViewType::PERSPECTIVE ? cameraPtr->GetProjectionMatrix() : cameraPtr->GetOrthoMatrix(), viewMatrix = cameraPtr->GetViewMatrix();

	// Render scene
	for (auto it : objectsInScene)
	{
		it->Render(projectionMatrix, viewMatrix);
	}

}

void Renderer::AddToScene(RenderableObject* object)
{
	objectsInScene.push_back(object);
}
void Renderer::RemoveFromScene(RenderableObject* object)
{
	std::vector<RenderableObject*>::iterator it = std::find_if(objectsInScene.begin(), objectsInScene.end(), [object](RenderableObject* obj)
		{
			return object == obj;
		}
	);
	if (it != objectsInScene.end())
	{
		objectsInScene.erase(it);
	}
}

void Renderer::Destroy()
{
	// delete all objects in the scene
	for (auto it : objectsInScene)
	{
		delete it;
	}
}

void Renderer::SwitchWorldViewType()
{
	worldViewType = worldViewType == WorldViewType::PERSPECTIVE ? WorldViewType::ORTHOGRAPHIC : WorldViewType::PERSPECTIVE;
}