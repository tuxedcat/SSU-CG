#pragma once
#include "GameObject.h"

class Sphere: public GameObject{
private:
    void onDraw() override{
        glutSolidSphere(1, 10, 10);
    }
};