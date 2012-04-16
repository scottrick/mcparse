#include "GLScene.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include "etc\Matrix44.h"

GLScene::GLScene()
{
    camera.pq.pos.x = 4.0f;
}

GLScene::~GLScene()
{

}

void GLScene::render()
{
//	GLfloat fLightPos[] = { m_pCamera->GetPosQuat().pos.x, m_pCamera->GetPosQuat().pos.y, m_pCamera->GetPosQuat().pos.z };
//	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.333f, 0.1f, 100.0f);

    ////rotate to camera orientation
    //glMultMatrixf(camera.pq.quat.toMatrix().getRotationalInverse().m);

    ////translate to the camera's position
    //glTranslatef(-camera.pq.pos.x, -camera.pq.pos.y, -camera.pq.pos.z);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, 1.0f, -5.0f);

    //render the origin as a test
    testOrigin.render();
}