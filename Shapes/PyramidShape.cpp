#include "PyramidShape.h"


PyramidShape::PyramidShape(Shader* shaderPtr, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
    : RenderableObject(shaderPtr, position, rotation, scale, color)
{
	Init();
}

void PyramidShape::Init()
{
    // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions    // Colors (r,g,b,a)

        //basis 
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        //left side 
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.0f,  0.5f,  0.0f,

         //right side  
         0.5f, -0.5f,  0.5f,
         0.5f,  -0.5f, -0.5f,
         0.0f, 0.5f, 0.0f,

         //front side  
         -0.5f,  -0.5f, 0.5f,
          0.5f,  -0.5f, 0.5f, 
          0.0f,  0.5f, 0.0f,

          //back side  
          0.5f, -0.5f, -0.5f, 
         -0.5f, -0.5f, -0.5f, 
          0.0f,   0.5f, 0.0f,
    };

    // Index data to share position data
    GLushort indices[] = {
        // 1 triangle
        0, 1, 2,
        // 2 triangle
        3, 4, 5,
        // 3 triangle
        6, 7, 8,
        // 4 triangle
        9, 10, 11,
        // 5 triangle
        12, 13, 14,
        // 6 triangle
        15, 16, 17
    };

    const GLuint floatsPerVertex = 3;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * floatsPerVertex;// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);
}