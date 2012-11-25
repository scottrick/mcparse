#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "GLScene.h"

class GLContext
{
public:
    GLContext();
    ~GLContext();

    void create(int *argcp, char **argv);
    void destroy();

    void dumpExtensions();
    void dumpInfo();

    GLScene *getScene();

protected:


private:
    GLScene scene;

};

#endif