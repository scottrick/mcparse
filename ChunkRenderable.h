#pragma once

#include "opengl/GLRenderable.h"
#include <GL/glew.h>

class Chunk;

class ChunkRenderable : public GLRenderable
{
public:
	ChunkRenderable(Chunk *pNewChunk);

	//renderable
	void render() const;
    GLuint getShaderProgram() const;

    //unknown
    const char *getClassName() const;

protected:
	~ChunkRenderable();

	void setChunk(Chunk *pNewChunk);
	void makeBuffers();
	void destroyBuffers();

	Chunk *pChunk;

	GLuint shaderProgram;

    GLuint vbo;
    GLuint ebo;

};

