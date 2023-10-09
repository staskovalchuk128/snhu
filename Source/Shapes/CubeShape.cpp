#include "CubeShape.h"

CubeShape::CubeShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
    : RenderableObject(shaderPtr, position, rotation, scale, color)
{
    Init();
}

void CubeShape::Init()
{
    std::vector<GLfloat> vertexData = {
        // Bottom face                                      
        -.5f, -.5f, -.5f, 0.0f,  0.0f,  -1.0f,  0.0f, 0.0f,   //0      
        .5f, -.5f, -.5f,  0.0f,  0.0f,  -1.0f,  1.0f, 0.0f,   //1                
        .5f, .5f, -.5f,   0.0f,  0.0f,  -1.0f,  1.0f, 1.0f,   //2                
        -.5f, .5f, -.5f,  0.0f,  0.0f,  -1.0f,  0.0f, 1.0f,   //3                
        // Top face                              
        -.5f, -.5f, .5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,   //4     
        .5f, -.5f, .5f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f,   //5     
        .5f, .5f, .5f,    0.0f,  0.0f,  1.0f,  1.0f, 1.0f,   //6     
        -.5f, .5f, .5f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f,   //7    
        // Left face                                       
        -.5f, .5f, .5f,   -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,   //8   
        -.5f, .5f, -.5f,  -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,   //9     
        -.5f, -.5f, -.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,   //10         
        -.5f, -.5f, .5f,  -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,   //11       
        // Right face                                      
        .5f, .5f, .5f,    1.0f,  0.0f,  0.0f,  1.0f, 0.0f,   //12           
        .5f, .5f, -.5f,   1.0f,  0.0f,  0.0f,  1.0f, 1.0f,   //13         
        .5f, -.5f, -.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,   //14         
        .5f, -.5f, .5f,   1.0f,  0.0f,  0.0f,  0.0f, 0.0f,   //15        
        // Back face
        -.5f, -.5f, -.5f, 0.0f,  -1.0f,  0.0f,  0.0f, 1.0f,   //16
        .5f, -.5f, -.5f,  0.0f,  -1.0f,  0.0f,  1.0f, 1.0f,   //17
        .5f, -.5f, .5f,   0.0f,  -1.0f,  0.0f,  1.0f, 0.0f,   //18
        -.5f, -.5f, .5f,  0.0f,  -1.0f,  0.0f,  0.0f, 0.0f,   //19
        // Front Face
        -.5f, .5f, -.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,    //20
        .5f, .5f, -.5f,   0.0f,  1.0f,  0.0f,  1.0f, 1.0f,    //21
        .5f, .5f, .5f,    0.0f,  1.0f,  0.0f,  1.0f, 0.0f,    //22
        -.5f, .5f, .5f,   0.0f,  1.0f,  0.0f,  0.0f, 0.0f     //23
    };

    std::vector<GLushort> indices = {
        0, 1, 2, 2, 3, 0,       // Bottom
        4, 5, 6, 6, 7, 4,       // Top
        8, 9, 10, 10, 11, 8,    // Left
        12, 13, 14, 14, 15, 12, // Right
        16, 17, 18, 18, 19, 16, // Back
        20, 21, 22, 22, 23, 20  // Front
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerTexCoord = 2;

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
    GLint stride = sizeof(GLfloat) * (floatsPerVertex + floatsPerNormal + floatsPerTexCoord);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerTexCoord, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}



