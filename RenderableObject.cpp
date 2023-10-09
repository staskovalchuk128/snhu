#include "RenderableObject.h"
#include "Shader.h"
#include "Texture.h"

RenderableObject::RenderableObject(Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
	: shaderPtr(shader), position(position), rotation(rotation), scale(scale), color(color)
{
	mesh = {};
	mesh.texture = NULL;
	position = rotation = localOffset = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	modelMatrix = glm::mat4(1.0f);

	UpdateMatrix();
}

RenderableObject::~RenderableObject()
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(2, mesh.vbos);
}



void RenderableObject::Render(const glm::mat4 projectionMatrix, const glm::mat4 viewMatrix)
{
	//Check if shader exists
	assert(shaderPtr);

	// bind the shader and pass matrices
	shaderPtr->Bind();
	shaderPtr->SetMat4("projection", projectionMatrix);
	shaderPtr->SetMat4("view", viewMatrix);
	shaderPtr->SetMat4("model", modelMatrix);
	shaderPtr->SetVec4("color", color);

	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(-4.0f,  3.5f,  2.0f),
		glm::vec3(6.0f,  3.5f,  2.0f),
	};

	// directional light
	shaderPtr->SetVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shaderPtr->SetVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shaderPtr->SetVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shaderPtr->SetVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	// point light 1
	shaderPtr->SetVec3("pointLights[0].position", pointLightPositions[0]);
	shaderPtr->SetVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shaderPtr->SetVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shaderPtr->SetVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shaderPtr->SetFloat("pointLights[0].constant", 1.0f);
	shaderPtr->SetFloat("pointLights[0].linear", 0.09f);
	shaderPtr->SetFloat("pointLights[0].quadratic", 0.032f);

	// point light 2
	shaderPtr->SetVec3("pointLights[1].position", pointLightPositions[1]);
	shaderPtr->SetVec3("pointLights[1].ambient", glm::vec3(0.2f, 0.05f, 0.05f));
	shaderPtr->SetVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shaderPtr->SetVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shaderPtr->SetFloat("pointLights[1].constant", 1.0f);
	shaderPtr->SetFloat("pointLights[1].linear", 0.09f);
	shaderPtr->SetFloat("pointLights[1].quadratic", 0.032f);



	shaderPtr->SetInt("material.diffuse", 0);
	shaderPtr->SetInt("material.specular", 1);
	shaderPtr->SetFloat("material.shininess", 32.0f);

	//Let shader know if texture exists
	shaderPtr->SetBool("textureExists", !!mesh.texture);

	glBindVertexArray(mesh.vao);

	//If texture exsts, bind the texture
	if (mesh.texture)
	{
		mesh.texture->Bind();
		mesh.texture->Bind(1);

	}

	glDrawElements(GL_TRIANGLES, mesh.nIndices, GL_UNSIGNED_SHORT, NULL); // Draws the object

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void RenderableObject::UpdateMatrix()
{
	//calc matrix with local offset
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position + localOffset);
	modelMatrix = glm::translate(modelMatrix, -localOffset);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 1.0f, 1.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, localOffset);
	modelMatrix = glm::scale(modelMatrix, scale);
}

void RenderableObject::AttachTexture(const char* texturePath)
{
	mesh.texture = std::make_shared<Texture2D>(texturePath);
}

void RenderableObject::SetPosition(const glm::vec3& position)
{
	this->position = position;
	UpdateMatrix();
}
void RenderableObject::SetRotation(const glm::vec3& rotation)
{
	this->rotation = rotation;
	UpdateMatrix();
}
void RenderableObject::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
	UpdateMatrix();
}
void RenderableObject::SetLocalOffset(const glm::vec3& localOffset)
{
	this->localOffset = localOffset;
	UpdateMatrix();
}
void RenderableObject::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec3& RenderableObject::GetPosition()
{
	return scale;
}
const glm::vec3& RenderableObject::GetRotation()
{
	return rotation;
}
const glm::vec3& RenderableObject::GetScale()
{
	return scale;
}
const glm::vec3& RenderableObject::GetLocalOffset()
{
	return localOffset;
}
const glm::vec4& RenderableObject::GetColor()
{
	return color;
}
const glm::mat4& RenderableObject::GetModelMatrix()
{
	return modelMatrix;
}