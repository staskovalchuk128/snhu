#include "ConeShape.h"

ConeShape::ConeShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color,
	float height, float bottomRadius, int sliceCount, int stackCount)
	: RenderableObject(shaderPtr, position, rotation, scale, color)
{
	Init(height, bottomRadius, sliceCount, stackCount);
}

void ConeShape::Init(float height, float bottomRadius, int sliceCount, int stackCount)
{
	float topRadius = 0.0f;

	std::vector<GLfloat> vertexData;
	std::vector<GLushort> indices;

	float stackHeight = height / stackCount;
	float radiusStep = (topRadius - bottomRadius) / stackCount;
	int ringCount = stackCount + 1;

	for (int i = 0; i < ringCount; i++) {
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;
		float dTheta = 2.0f * glm::pi<float>() / sliceCount;
		for (int j = 0; j <= sliceCount; j++) {

			float c = cos(j * dTheta);
			float s = sin(j * dTheta);

			glm::vec3 v = glm::vec3(r * c, y, r * s);

			vertexData.push_back(v.x);
			vertexData.push_back(v.y);
			vertexData.push_back(v.z);

			//Texture coordinates
			vertexData.push_back((float)j / sliceCount);
			vertexData.push_back(1.0f - (float)i / stackCount);

		}
	}
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount; i++) {
		for (int j = 0; j < sliceCount; j++) {
			indices.push_back(i * ringVertexCount + j);
			indices.push_back((i + 1) * ringVertexCount + j);
			indices.push_back((i + 1) * ringVertexCount + j + 1);

			indices.push_back(i * ringVertexCount + j);
			indices.push_back((i + 1) * ringVertexCount + j + 1);
			indices.push_back(i * ringVertexCount + j + 1);
		}
	}

	/*BUILD TOP CAP*/

	int baseIndex = (int)vertexData.size();

	float y = 0.5f * height;
	float dTheta = 2.0f * glm::pi<float>() / sliceCount;

	for (int i = 0; i <= sliceCount; i++) {
		float x = topRadius * cos(i * dTheta);
		float z = topRadius * sin(i * dTheta);

		vertexData.push_back(x);
		vertexData.push_back(y);
		vertexData.push_back(z);
	}

	vertexData.push_back(0);
	vertexData.push_back(y);
	vertexData.push_back(0);

	int centerIndex = (int)vertexData.size() - 1;
	for (int i = 0; i < sliceCount; i++) {
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i + 1);
		indices.push_back(baseIndex + i);
	}
	/*BUILD BOTTOM CAP*/

	baseIndex = (int)vertexData.size();

	for (int i = 0; i <= sliceCount; i++) {
		float x = bottomRadius * cos(i * dTheta);
		float z = bottomRadius * sin(i * dTheta);

		vertexData.push_back(x);
		vertexData.push_back(y);
		vertexData.push_back(z);
	}

	vertexData.push_back(0);
	vertexData.push_back(y);
	vertexData.push_back(0);

	centerIndex = (int)vertexData.size() - 1;
	for (int i = 0; i < sliceCount; i++) {
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}



	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerTex = 2;

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
	GLint stride = sizeof(GLfloat) * (floatsPerVertex + floatsPerTex);// The number of floats before each

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerTex, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float)* floatsPerVertex));
	glEnableVertexAttribArray(1);
}
