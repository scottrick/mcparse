#ifndef _POSQUAT_
#define _POSQUAT_					1

#include "Quat.h"

class PosQuat
{
public:
	PosQuat();
	~PosQuat();

	void				Print(int indent = 0) const;

	//DATA
	VEC3				pos;
	Quat				quat;

private:
	void				Init();
};

#endif
