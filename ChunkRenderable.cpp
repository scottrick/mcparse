#include "ChunkRenderable.h"

#include "Chunk.h"
#include "cppNBT/src/cppnbt.h"
#include "opengl/GLShaderManager.h"

#include "opengl/glm/glm.hpp"
#include "opengl/glm/gtc/matrix_transform.hpp"
#include "opengl/glm/gtc/type_ptr.hpp"

#include <iostream>
using namespace std;

ChunkRenderable::ChunkRenderable(Chunk *pNewChunk)
	: pChunk(0), model(glm::mat4())
{
	setChunk(pNewChunk);
	makeBuffers();
}

ChunkRenderable::~ChunkRenderable()
{
	setChunk(0);
	destroyBuffers();
}

void ChunkRenderable::setChunk(Chunk *pNewChunk) 
{
	if (pChunk != pNewChunk)
	{
		if (pChunk)
		{
			pChunk->release();
			pChunk = 0;
		}

		if (pNewChunk)
		{
			pChunk = pNewChunk;
			pChunk->addRef();
		}
	}
}

void ChunkRenderable::makeBuffers()
{
    shaderProgram = GLShaderManager::Manager()->getShaderProgram("shaders/BasicChunk");

	model = glm::translate(glm::mat4(), glm::vec3((GLfloat)(pChunk->getChunkX() * CHUNK_WIDTH), 0.0f, (GLfloat)(pChunk->getChunkZ() * CHUNK_WIDTH)));

	GLfloat *pVertexData = new GLfloat[4096 * 24 * 4];
	GLuint *pElementData = new GLuint[4096 * 6 * 4];

    //setup the vertex and element index buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

	unsigned int vertexIndex = 0;
	numElements = 0;
	
	for (unsigned int x = 0; x < CHUNK_WIDTH; ++x)
	{
		for (unsigned int z = 0; z < CHUNK_WIDTH; ++z)
		{
			for (unsigned int y = 0; y < CHUNK_HEIGHT; ++y)
			{
				unsigned int blockId = pChunk->getBlockIdAt(x, y, z);

				if (!blockId) 
				{ //AIR block, so do nothing
					continue;
				}

				//get the 6 adjacent blocks
				unsigned int top = pChunk->getBlockIdAt(x, y + 1, z);
				unsigned int bottom = pChunk->getBlockIdAt(x, y - 1, z);
				unsigned int xPlus = pChunk->getBlockIdAt(x + 1, y, z);
				unsigned int xMinus = pChunk->getBlockIdAt(x - 1, y, z);
				unsigned int zPlus = pChunk->getBlockIdAt(x, y, z + 1);
				unsigned int zMinus = pChunk->getBlockIdAt(x, y, z - 1);

				GLfloat r, g, b;

				if (blockId == 7) 
				{ //bedrock
					r = 0.1f;
					g = 0.1f;
					b = 0.1f;
				}
				else if (blockId == 1) 
				{ //stone
					r = 0.5f;
					g = 0.5f;
					b = 0.5f;
				}
				else if (blockId == 8 || blockId == 9) 
				{ //water
					r = 0.0f;
					g = 0.0f;
					b = 0.6f;
				}
				else if (blockId == 2) 
				{ //grass
					r = 0.0f;
					g = 0.6f;
					b = 0.0f;
				}
				else if (blockId == 3) 
				{ //dirt
					r = 0.54f;
					g = 0.27f;
					b = 0.07f;
				}
				else if (blockId == 73) 
				{ //redstone
					r = 1.0f;
					g = 0.0f;
					b = 0.0f;
				}
				else if (blockId == 56) 
				{ //diamond
					r = 0.2f;
					g = 0.2f;
					b = 1.0f;
				}
				else
				{
					r = 1.0f;
					g = 0.0f;
					b = 1.0f;
				}

				if (!top)
				{ //add top triangles
					unsigned int vertexStart = vertexIndex / 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pElementData[numElements + 0] = vertexStart + 3;
					pElementData[numElements + 1] = vertexStart + 0;
					pElementData[numElements + 2] = vertexStart + 1;
					pElementData[numElements + 3] = vertexStart + 3;
					pElementData[numElements + 4] = vertexStart + 1;
					pElementData[numElements + 5] = vertexStart + 2;
					numElements += 6;
				}

				if (!bottom)
				{ //add bottom triangles
					unsigned int vertexStart = vertexIndex / 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pElementData[numElements + 0] = vertexStart + 2;
					pElementData[numElements + 1] = vertexStart + 1;
					pElementData[numElements + 2] = vertexStart + 0;
					pElementData[numElements + 3] = vertexStart + 3;
					pElementData[numElements + 4] = vertexStart + 2;
					pElementData[numElements + 5] = vertexStart + 0;
					numElements += 6;
				}

				if (!xMinus)
				{ //add xMinus triangles
					unsigned int vertexStart = vertexIndex / 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pElementData[numElements + 0] = vertexStart + 1;
					pElementData[numElements + 1] = vertexStart + 0;
					pElementData[numElements + 2] = vertexStart + 3;
					pElementData[numElements + 3] = vertexStart + 3;
					pElementData[numElements + 4] = vertexStart + 2;
					pElementData[numElements + 5] = vertexStart + 1;
					numElements += 6;
				}

				if (!xPlus)
				{ //add xPlus triangles
					unsigned int vertexStart = vertexIndex / 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pElementData[numElements + 0] = vertexStart + 1;
					pElementData[numElements + 1] = vertexStart + 3;
					pElementData[numElements + 2] = vertexStart + 0;
					pElementData[numElements + 3] = vertexStart + 1;
					pElementData[numElements + 4] = vertexStart + 2;
					pElementData[numElements + 5] = vertexStart + 3;
					numElements += 6;
				}

				if (!zMinus)
				{ //add zMinus triangles
					unsigned int vertexStart = vertexIndex / 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pElementData[numElements + 0] = vertexStart + 0;
					pElementData[numElements + 1] = vertexStart + 2;
					pElementData[numElements + 2] = vertexStart + 1;
					pElementData[numElements + 3] = vertexStart + 0;
					pElementData[numElements + 4] = vertexStart + 3;
					pElementData[numElements + 5] = vertexStart + 2;
					numElements += 6;
				}

				if (!zPlus)
				{ //add zPlus triangles
					unsigned int vertexStart = vertexIndex / 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x + 1.0f;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pVertexData[vertexIndex + 0] = (GLfloat)x;
					pVertexData[vertexIndex + 1] = (GLfloat)y + 1.0f;
					pVertexData[vertexIndex + 2] = (GLfloat)z + 1.0f;
					pVertexData[vertexIndex + 3] = r; //r
					pVertexData[vertexIndex + 4] = g; //g
					pVertexData[vertexIndex + 5] = b; //b
					vertexIndex += 6;

					pElementData[numElements + 0] = vertexStart + 0;
					pElementData[numElements + 1] = vertexStart + 1;
					pElementData[numElements + 2] = vertexStart + 2;
					pElementData[numElements + 3] = vertexStart + 0;
					pElementData[numElements + 4] = vertexStart + 2;
					pElementData[numElements + 5] = vertexStart + 3;
					numElements += 6;
				}
			}
		}
	}

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexIndex, pVertexData, GL_STATIC_DRAW);

    //setup ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(GLuint), pElementData, GL_STATIC_DRAW);

	//delete data buffers for now
	delete pVertexData;
	delete pElementData;
}

void ChunkRenderable::destroyBuffers()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

const glm::mat4 &ChunkRenderable::getModelMatrix() const
{
	return model;
}

GLuint ChunkRenderable::getShaderProgram() const 
{
    return shaderProgram;
}

void ChunkRenderable::render() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));

	GLuint modelTransformUniform = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

const char *ChunkRenderable::getClassName() const 
{
    return "ChunkRenderable";
}
