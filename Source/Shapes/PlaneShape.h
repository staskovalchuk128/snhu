#pragma once
#include "..//RenderableObject.h"

class PlaneShape : public RenderableObject
{
public:
	PlaneShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
private:
	void Init();
};

