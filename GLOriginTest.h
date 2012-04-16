#ifndef _GL_ORIGIN_TEST_
#define _GL_ORIGIN_TEST_

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
    GLuint vertexArrayID;  
};

#endif