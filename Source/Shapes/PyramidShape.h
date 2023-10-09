#pragma once
#include "..//RenderableObject.h"

class PyramidShape : public RenderableObject
{
public:
	PyramidShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);
private:
	void Init();
};

