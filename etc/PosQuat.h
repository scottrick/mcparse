#ifndef _POSQUAT_
#define _POSQUAT_					1

#include "Quat.h"

class PosQuat
{
public:
	PosQuat();
	~PosQuat();

	void        print(int indent = 0) const;

	VEC3        pos;
	Quat        quat;

private:

};

#endif
