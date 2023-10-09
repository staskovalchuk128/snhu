#include "CylinderShape.h"

CylinderShape::CylinderShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color,
	float height, float bottomRadius, float topRadius, int sliceCount, int stackCount)
	: RenderableObject(shaderPtr, position, rotation, scale, color)
{
	Init(height, bottomRadius, topRadius, sliceCount, stackCount);
}

void CylinderShape::Init(float height, float bottomRadius, float topRadius, int sliceCount, int stackCount)
{
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

			//Normals
			vertexData.push_back(r * c);
			vertexData.push_back(y);
			vertexData.push_back(r * s);


			//Texture coordinates
			vertexData.push_back(j / (float)stackCount);
			vertexData.push_back(i / (float)sliceCount);
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
	
	int baseIndex = (sliceCount + 1) * (stackCount + 1);
	int centerIndex = baseIndex + (sliceCount + 1);


	float y = 0.5f * height;
	float dTheta = float(2.0f * glm::pi<float>()) / sliceCount;

	for (int i = sliceCount; i >= 0; i--) {
		float x = topRadius * cos(i * dTheta);
		float z = topRadius * sin(i * dTheta);
		float U = cos(i * dTheta) / 2.0 + 0.5;
		float V = sin(i * dTheta) / 2.0 + 0.5;

		vertexData.push_back(x);
		vertexData.push_back(y);
		vertexData.push_back(z);

		//Normals
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);

		//Texture coordinates
		vertexData.push_back(U);
		vertexData.push_back(V);

	}

	vertexData.push_back(0);
	vertexData.push_back(y);
	vertexData.push_back(0);

	//Normals
	vertexData.push_back(0.0f);
	vertexData.push_back(1.0f);
	vertexData.push_back(0.0f);

	//Texture coordinates
	vertexData.push_back(0.5f);
	vertexData.push_back(0.5f);


	for (int i = 0; i < sliceCount; i++) {
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}

	/*BUILD BOTTOM CAP*/
	baseIndex = centerIndex + 1;
	centerIndex = baseIndex + (sliceCount + 1);

	y = -0.5f * height;

	for (int i = 0; i <= sliceCount; i++) {
		float x = bottomRadius * cos(i * dTheta);
		float z = bottomRadius * sin(i * dTheta);
		float U = cos(i * dTheta) / 2.0 + 0.5;
		float V = sin(i * dTheta) / 2.0 + 0.5;

		vertexData.push_back(x);
		vertexData.push_back(y);
		vertexData.push_back(z);

		//Normals
		vertexData.push_back(0.0f);
		vertexData.push_back(-1.0f);
		vertexData.push_back(0.0f);

		//Texture coordinates
		vertexData.push_back(U);
		vertexData.push_back(V);
	}
	vertexData.push_back(0);
	vertexData.push_back(y);
	vertexData.push_back(0);


	//Normals
	vertexData.push_back(0.0f);
	vertexData.push_back(-1.0f);
	vertexData.push_back(0.0f);

	//Texture coordinates
	vertexData.push_back(0.5f);
	vertexData.push_back(0.5f);

	for (int i = 0; i < sliceCount; i++) {
		indices.push_back(centerIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}


	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
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

	// Strides between vertex coordinates
	GLint stride = sizeof(GLfloat) * (floatsPerVertex + floatsPerNormal + floatsPerTex);// The number of floats before each

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float)* floatsPerVertex));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerTex, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float)* (floatsPerVertex + floatsPerNormal)));
	glEnableVertexAttribArray(2);
}