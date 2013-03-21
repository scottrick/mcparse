#include "ChunkRenderable.h"

#include "Chunk.h"
#include "cppNBT/src/cppnbt.h"
#include "opengl/GLShaderManager.h"

ChunkRenderable::ChunkRenderable(Chunk *pNewChunk)
	: pChunk(0)
{
	setChunk(pNewChunk);

	pNewChunk->dump();

	nbt::NbtBuffer *pBuffer = pChunk->getBuffer();
	
	nbt::TagCompound *root = (nbt::TagCompound *)pBuffer->getRoot();
	nbt::TagCompound *level = (nbt::TagCompound *)root->getValueAt("Level");
	nbt::TagList *sections = (nbt::TagList *)level->getValueAt("Sections");

	//just get the top section blocks for now
	nbt::TagCompound *topSection = (nbt::TagCompound *)sections->back();
	nbt::TagByteArray *blocks = (nbt::TagByteArray *)topSection->getValueAt("Blocks");

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

    //setup the vertex and element index buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 6, vertices, GL_STATIC_DRAW);

    ////setup ebo
    //this->numElements = numElements;
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(GLuint), elements, GL_STATIC_DRAW);
}

void ChunkRenderable::destroyBuffers()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

GLuint ChunkRenderable::getShaderProgram() const 
{
    return shaderProgram;
}

void ChunkRenderable::render() const 
{
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    //GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    //glEnableVertexAttribArray(posAttrib);
    //glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    //GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
    //glEnableVertexAttribArray(colorAttrib);
    //glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));

    //GLuint modelTransformUniform = glGetUniformLocation(shaderProgram, "model");
    //glm::mat4 modelTransform = glm::mat4(); //identity model transformation for now
    //glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));

    //glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

const char *ChunkRenderable::getClassName() const 
{
    return "ChunkRenderable";
}