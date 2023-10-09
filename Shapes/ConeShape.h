#pragma once
#include "..//RenderableObject.h"

class ConeShape : public RenderableObject
{
public:
	ConeShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float height, float bottomRadius = 0.5f, int sliceCount = 32, int stackCount = 32);
private:
	void Init(float height, float bottomRadius, int sliceCount, int stackCount);
};

