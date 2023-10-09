#pragma once
#include <vector>

class RenderableObject;
class Camera;

enum struct WorldViewType
{
	PERSPECTIVE, ORTHOGRAPHIC
};

class Renderer
{
public:
	static void Init(Camera* cameraPtr);
	static void Destroy();

	static void Render();
	
	static void AddToScene(RenderableObject* object);
	static void RemoveFromScene(RenderableObject* object);

	static void SwitchWorldViewType();
private:
	static WorldViewType worldViewType;
	static Camera* cameraPtr;
	static std::vector<RenderableObject*> objectsInScene;
};

