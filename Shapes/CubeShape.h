#pragma once
#include "..//RenderableObject.h"

class CubeShape : public RenderableObject
{
public:
	CubeShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);
private:
	void Init();
};

