#ifndef _GL_CAMERA_
#define _GL_CAMERA_

#include "etc\PosQuat.h"

class GLCamera
{
public:
    GLCamera();
    ~GLCamera();

    PosQuat pq;
    float fov;

protected:


private:

};

#endif