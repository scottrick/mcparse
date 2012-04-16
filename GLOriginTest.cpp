#include "GLOriginTest.h"

#include <iostream>
using namespace std;

GLOriginTest::GLOriginTest()
{
    vaoID = 0;
    vertexVBO_ID = 0;
}

GLOriginTest::~GLOriginTest()
{

}

void GLOriginTest::render()
{
    if (vaoID <= 0 || vertexVBO_ID <= 0)
    {
        setupBuffer();
    }

    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
}

void GLOriginTest::setupBuffer()
{
    const unsigned int SIZE_OF_VERTEX_DATA = 24;
    float vertexData[SIZE_OF_VERTEX_DATA];
    vertexData[0] = 0.0f; // (0, 0, 0)
    vertexData[1] = 0.0f;
    vertexData[2] = 0.0f;
    vertexData[3] = 1.0f;
    vertexData[4] = 1.0f;
    vertexData[5] = 1.0f;

    vertexData[6] = 1.0f; // (1, 0, 0)
    vertexData[7] = 0.0f;
    vertexData[8] = 0.0f;
    vertexData[9] = 1.0f;
    vertexData[10] = 0.0f;
    vertexData[11] = 0.0f;

    vertexData[12] = 0.0f; // (0, 1, 0)
    vertexData[13] = 1.0f;
    vertexData[14] = 0.0f;
    vertexData[15] = 0.0f;
    vertexData[16] = 1.0f;
    vertexData[17] = 0.0f;

    vertexData[18] = 0.0f; // (0, 0, 1);
    vertexData[19] = 0.0f;
    vertexData[20] = 1.0f;
    vertexData[21] = 0.0f;
    vertexData[22] = 0.0f;
    vertexData[23] = 1.0f;

    unsigned short indices[6];  
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 0;
    indices[3] = 2;
    indices[4] = 0;
    indices[5] = 3;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &vertexVBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_ID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SIZE_OF_VERTEX_DATA, vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));
    
    glGenBuffers(1, &indexVBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 6, indices, GL_STATIC_DRAW);
}