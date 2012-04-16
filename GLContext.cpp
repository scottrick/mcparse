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

    g_pGLContext = this;

    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 300);
    glutCreateWindow("GLContext");
    glutDisplayFunc(&glDisplayFunc);
    glutIdleFunc(&glIdleFunc);
    glutReshapeFunc(&glReshapeFunc);

    dumpInfo();
    dumpExtensions();

    GLenum initError = glewInit();
    if (initError != GLEW_OK)
    {
        cout << "glewInit failed [" << initError << "]" << endl;
        return;
    }

    glutMainLoop();
}

void GLContext::destroy()
{
    if (g_pGLContext)
    { //we have something to destroy!
        
    }
}

void GLContext::dumpExtensions()
{
    const GLubyte* data = glGetString(GL_EXTENSIONS);
    unsigned int len = strlen((char*)data) + 1; //+1 to copy the null terminator
    GLubyte* extensions = new GLubyte[len];
    
    memcpy(extensions, data, len);
    GLubyte* current = extensions;

    while (*current != '\0')
    {
        if (*current == ' ')
        {
            *current = '\n';
        }

        current++;
    }

    cout << "==================================================" << endl;
    cout << "GL_EXTENSIONS" << endl;
    cout << "==================================================" << endl; 
    cout << extensions << endl;
    cout << "==================================================" << endl; 

    delete[] extensions;
}

void GLContext::dumpInfo()
{
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* shaderLang = glGetString(GL_SHADING_LANGUAGE_VERSION);

    cout << "GL_VERSION:   " << version << endl;
    cout << "GL_RENDERER:  " << renderer << endl;
    cout << "GL_VENDOR:    " << vendor << endl;
    cout << "GL_SHADELANG: " << shaderLang << endl;
}

GLScene *GLContext::getScene()
{
    return &scene;
}

void glDisplayFunc()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    g_pGLContext->getScene()->render();

    glutSwapBuffers();
}

void glIdleFunc()
{

}

void glReshapeFunc(int sizeX, int sizeY)
{
    cout << "glReshapeFunc (" << sizeX << ", " << sizeY << ")" << endl;
}