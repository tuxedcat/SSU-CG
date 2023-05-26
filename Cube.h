#pragma once
#include "GameObject.h"

class Cube: public GameObject{
private:
    void onDraw() override{
        glutSolidCube(1);
    }
};