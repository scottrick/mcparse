#ifndef _ETC_DEF_
#define _ETC_DEF_				1

#include <cassert>
#include <cmath>
using namespace std;

#define						MATH_NORMALIZATION_ALLOWABLE_ERROR			0.000000001f
#define						PI											3.141592654f

static float				InvSqrt(float x);

struct VEC2
{
    VEC2() : x(0.0f), y(0.0f) { }
	VEC2(float const& fX, float const& fY) : x(fX), y(fY) { }

	float x, y;

    VEC2 operator- (VEC2 const& vSub)
    {
        VEC2 temp(x - vSub.x, y - vSub.y);
        return temp;
    }
    
    VEC2 operator+ (VEC2 const& vAdd)
    {
        VEC2 temp(x + vAdd.x, y + vAdd.y);
        return temp;
    }
};

struct VEC3
{
    VEC3() : x(0.0f), y(0.0f), z(0.0f) { }
    VEC3(float const& fX, float const& fY, float const& fZ) : x(fX), y(fY), z(fZ) { }

	float x, y, z;

	VEC3 operator- (VEC3 const& vSub) 
    {
        VEC3 temp(x - vSub.x, y - vSub.y, z - vSub.z);
        return temp;
    }

    VEC3 operator+ (VEC3 const& vAdd)
    {
        VEC3 temp(x + vAdd.x, y + vAdd.y, z + vAdd.z);
        return temp;
    }
};

struct VEC4
{
    VEC4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
	VEC4(float const& fX, float const& fY, float const& fZ, float const& fW): x(fX), y(fY), z(fZ), w(fW) { }

	float x, y, z, w;

    VEC4 operator- (VEC4 const& vSub)
    {
        VEC4 temp(x - vSub.x, y - vSub.y, z - vSub.z, w - vSub.w);
        return temp;
    }

    VEC4 operator+ (VEC4 const& vAdd)
    {
        VEC4 temp(x + vAdd.x, y + vAdd.y, z + vAdd.z, w + vAdd.w);
        return temp;
    }
};

struct VECTOR2_INT
{
	VECTOR2_INT()										{ x = 0;		y = 0; }
	VECTOR2_INT(int dwX, int dwY)						{ x = dwX;		y = dwY; }

	int x, y;
};

static VEC3 CrossProduct(VEC3 const& vec1, VEC3 const& vec2)
{
	VEC3 newVec;
	newVec.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	newVec.y = -((vec1.x * vec2.z) - (vec1.z * vec2.x));
	newVec.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

	return newVec;
}

static float MagnitudeSquaredVECTOR3(VEC3 const& vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}	

static void NormalizeVEC2(VEC2 &vec)
{
	float magnitude = (vec.x * vec.x) + (vec.y * vec.y);

	if (abs(magnitude - 1.0f) > MATH_NORMALIZATION_ALLOWABLE_ERROR)
	{
		//assert(magnitude > MATH_NORMALIZATION_ALLOWABLE_ERROR); //make sure any vector being normalized has some non-zero magnitude
        magnitude = InvSqrt(magnitude);
		vec.x = vec.x * magnitude;
		vec.y = vec.y * magnitude;
	}
}	

static void NormalizeVEC3(VEC3 &vec)
{
	float magnitude = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);

	if (abs(magnitude - 1.0f) > MATH_NORMALIZATION_ALLOWABLE_ERROR)
	{
		//assert(magnitude > MATH_NORMALIZATION_ALLOWABLE_ERROR); //make sure any vector being normalized has some non-zero magnitude
		magnitude = InvSqrt(magnitude);
		vec.x = vec.x * magnitude;		
		vec.y = vec.y * magnitude;
		vec.z = vec.z * magnitude;
	}
}	

static void NormalizeVEC4(VEC4 &vec)
{
	float magnitude = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w);

	if (abs(magnitude - 1.0f) > MATH_NORMALIZATION_ALLOWABLE_ERROR)
	{
		//assert(magnitude > MATH_NORMALIZATION_ALLOWABLE_ERROR); //make sure any vector being normalized has some non-zero magnitude
		magnitude = InvSqrt(magnitude);
		vec.x = vec.x * magnitude;
		vec.y = vec.y * magnitude;
		vec.z = vec.z * magnitude;
		vec.w = vec.w * magnitude;
	}
}	

//Fast approximation of  "1 / sq rt(x)"
//http://www.beyond3d.com/content/articles/8/
static float InvSqrt (float x)
{
    float	xhalf		= 0.5f*x;
    int		i			= *(int*)&x;

    i		= 0x5f3759df - (i>>1);
    x		= *(float*)&i;
    x		= x*(1.5f - xhalf*x*x);

    return x;
}

#endif 