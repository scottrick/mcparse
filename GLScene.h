#ifndef _GL_SCENE_
#define _GL_SCENE_

#include "GLCamera.h"
#include "GLOriginTest.h"

class GLScene
{
public:
    GLScene();
    ~GLScene();

    void render();

protected:


private:
    GLCamera camera;
    GLOriginTest testOrigin;

};

#endif