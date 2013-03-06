#pragma once

#include "opengl/GLScene.h"

class MCScene : public GLScene
{
public:
	MCScene();

	void render();

    //from Unknown
    virtual const char *GetClassName() const;

protected:
	~MCScene();

};

