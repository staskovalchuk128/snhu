#include "SphereShape.h"

SphereShape::SphereShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color,
	float radius, int sliceCount, int stackCount)
	: RenderableObject(shaderPtr, position, rotation, scale, color)
{
	Init(radius, sliceCount, stackCount);
}

void SphereShape::Init(float radius, int sliceCount, int stackCount)
{
	std::vector<GLfloat> vertexData;
	std::vector<GLushort> indices;

	vertexData.push_back(0);
	vertexData.push_back(radius);
	vertexData.push_back(0);
	float phiStep = glm::pi<float>() / stackCount;
	float thetaStep = 2.0f * glm::pi<float>() / sliceCount;

	for (int i = 1; i <= stackCount - 1; i++) {
		float phi = i * phiStep;
		for (int j = 0; j <= sliceCount; j++) {
			float theta = j * thetaStep;
			glm::vec3 p = glm::vec3(
				(radius * sin(phi) * cos(theta)),
				(radius * cos(phi)),
				(radius * sin(phi) * sin(theta))
			);
			vertexData.push_back(p.x);
			vertexData.push_back(p.y);
			vertexData.push_back(p.z);
		}
	}
	vertexData.push_back(0);
	vertexData.push_back(-radius);
	vertexData.push_back(0);

	for (int i = 1; i <= sliceCount; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}
	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; i++) {
		for (int j = 0; j < sliceCount; j++) {
			indices.push_back(baseIndex + i * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}
	int southPoleIndex = (int)vertexData.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < sliceCount; i++) {
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}

	const GLuint floatsPerVertex = 3;

	glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	// Create 2 buffers: first one for the vertex data; second one for the indices
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), &vertexData[0], GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU


	mesh.nIndices = (GLuint)indices.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

	// Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
	GLint stride = sizeof(GLfloat) * (floatsPerVertex);// The number of floats before each

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);
}
