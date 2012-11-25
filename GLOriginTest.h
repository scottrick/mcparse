#ifndef _GL_ORIGIN_TEST_
#define _GL_ORIGIN_TEST_

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

class GLOriginTest
{
public:
    GLOriginTest();
    ~GLOriginTest();

    void render();

protected:

    void setupBuffer();

private:
    GLuint vaoID;  
    GLuint vertexVBO_ID;
    GLuint indexVBO_ID;
};

#endif