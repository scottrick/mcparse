#pragma once

#include "opengl/GLScene.h"

class MCScene : public GLScene
{
public:
	MCScene();

	//creation and deletion of this scene
	void create();
	void destroy();

	//rendering
	void prepareRender();
	void render();

    //from Unknown
    virtual const char *GetClassName() const;

protected:
	~MCScene();

};

