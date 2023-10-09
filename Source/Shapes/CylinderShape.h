#pragma once
#include "..//RenderableObject.h"

class CylinderShape : public RenderableObject
{
public:
	CylinderShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float height, float bottomRadius = 0.5f, float topRadius = 0.5f, int sliceCount = 32, int stackCount = 32);
private:
	void Init(float height, float bottomRadius, float topRadius, int sliceCount, int stackCount);
};

