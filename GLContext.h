#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <GL/glew.h>
#include <GL/glut.h>

class GLContext
{
public:
    GLContext();
    ~GLContext();

    void create(int *argcp, char **argv);
    void destroy();

protected:


private:

};

#endif