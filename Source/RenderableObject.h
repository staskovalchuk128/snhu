#pragma once
#include <vector>
#include <memory>
// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

class Texture2D;
class Shader;

struct GLMesh
{
	GLuint vao;         // Handle for the vertex array object
	GLuint vbos[2];     // Handles for the vertex buffer objects
	GLuint nVertices;    // Number of vertices of the mesh
	GLuint nIndices;    // Number of indices of the mesh
	std::shared_ptr<Texture2D> texture; // Texture of the mesh
};

class RenderableObject
{
public:
	RenderableObject(Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);
	virtual ~RenderableObject();

	virtual void Render(const glm::mat4 projectionMatrix, const glm::mat4 viewMatrix);

	//Attaching texture to the mesh
	void AttachTexture(const char* texturePath);

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);
	void SetLocalOffset(const glm::vec3& localOffset);
	void SetColor(const glm::vec4& color);

	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();
	const glm::vec3& GetLocalOffset();
	const glm::vec4& GetColor();

	const glm::mat4& GetModelMatrix();
protected:
	GLMesh mesh;
private:
	glm::mat4 modelMatrix;

	glm::vec3 position, rotation, scale, localOffset;
	glm::vec4 color;

	Shader* shaderPtr;
private:
	void UpdateMatrix();
};

