#pragma once
#include "Core.h"

class Vec3{
public:
    float x,y,z;
    Vec3():Vec3(0,0,0){}
    Vec3(float x,float y,float z):x(x),y(y),z(z){}
};
ostream& operator<<(ostream& os, const Vec3& v){
    return os<<'('<<v.x<<','<<v.y<<','<<v.z<<')';
}