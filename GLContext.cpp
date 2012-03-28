#include "GLContext.h"

#include <cassert>
#include <iostream>
using namespace std;

static GLContext *g_pGLContext;

static void glDisplayFunc();
static void glIdleFunc();
static void glReshapeFunc(int sizeX, int sizeY);

GLContext::GLContext()
{

}

GLContext::~GLContext()
{
    destroy();
}

void GLContext::create(int *argcp, char **argv)
{
    assert(g_pGLContext == 0); //you can only have one context created at a time!

    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 300);
    glutCreateWindow("GLContext");
    glutDisplayFunc(&glDisplayFunc);
    glutIdleFunc(&glIdleFunc);
    glutReshapeFunc(&glReshapeFunc);

    glutMainLoop();
}

void GLContext::destroy()
{
    if (g_pGLContext)
    { //we have something to destroy!
        
    }
}

void glDisplayFunc()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}

void glIdleFunc()
{

}

void glReshapeFunc(int sizeX, int sizeY)
{
    cout << "glReshapeFunc (" << sizeX << ", " << sizeY << ")" << endl;
}