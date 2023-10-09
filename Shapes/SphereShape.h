#pragma once
#include "..//RenderableObject.h"

class SphereShape : public RenderableObject
{
public:
	SphereShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float radius, int sliceCount = 32, int stackCount = 32);
private:
	void Init(float radius, int sliceCount, int stackCount);
};

