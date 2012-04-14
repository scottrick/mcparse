#include "PosQuat.h"

#include <iostream>
using namespace std;

PosQuat::PosQuat()
{

}

PosQuat::~PosQuat()
{

}

void PosQuat::print(int indent) const
{
	printf("%*sPosQuat 0x%p\n", indent, " ", this);
	printf("%*s  pos  (%f, %f, %f)\n", indent, " ", pos.x, pos.y, pos.z);
	printf("%*s  quat (%f, %f, %f, %f)\n", indent, " ", quat.x, quat.y, quat.z, quat.w);
}
