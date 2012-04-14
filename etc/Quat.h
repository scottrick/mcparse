#ifndef _QUAT_
#define _QUAT_					1

#include "etc_def.h"

class Matrix44;

class Quat
{
public:
	Quat();
    Quat(float const& angleRadians, float const& xAxis, float const& yAxis, float const& zAxis);
	~Quat();

	Quat        conjugate() const;
	void        normalize();
	void        print() const;
	Matrix44    toMatrix() const;

	float       x, y, z, w;

	Quat operator+ (Quat const& q);
	Quat operator* (Quat const& q);
	void operator= (Quat const& q);

private:

};

#endif