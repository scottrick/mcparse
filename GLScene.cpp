#include "GLScene.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include "etc\Matrix44.h"

GLScene::GLScene()
{

}

GLScene::~GLScene()
{

}

void GLScene::render()
{
//	GLfloat fLightPos[] = { m_pCamera->GetPosQuat().pos.x, m_pCamera->GetPosQuat().pos.y, m_pCamera->GetPosQuat().pos.z };
//	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);

    //rotate to camera orientation
    glMultMatrixf(camera.pq.quat.toMatrix().getRotationalInverse().m);

    //translate to the camera's position
    glTranslatef(-camera.pq.pos.x, -camera.pq.pos.y, -camera.pq.pos.z);

    //render the origin as a test
    testOrigin.render();
}