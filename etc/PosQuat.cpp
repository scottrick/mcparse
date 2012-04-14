#include "PosQuat.h"

#include <iostream>
using namespace std;

PosQuat::PosQuat()
{
	Init();	
}

PosQuat::~PosQuat()
{

}

void PosQuat::Init()
{
	pos.x	= 0.0f;
	pos.y	= 0.0f;
	pos.z	= 0.0f;
}

void PosQuat::Print(int indent) const
{
	printf("%*sPosQuat 0x%p\n", indent, " ", this);
	printf("%*s  pos  (%f, %f, %f)\n", indent, " ", pos.x, pos.y, pos.z);
	printf("%*s  quat (%f, %f, %f, %f)\n", indent, " ", quat.x, quat.y, quat.z, quat.w);
}
