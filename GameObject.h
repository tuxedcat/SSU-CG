#pragma once
#include "Core.h"
#include "Vec3.h"

class GameObject{
public:
    set<GameObject*> children;
    Vec3 pos;
    // Vec3 rot;
    Vec3 scale;
    GameObject():pos(),scale(1,1,1){}
    void adopt(GameObject* obj){
        children.insert(obj);
    }
    void abandon(GameObject *obj){
        children.erase(obj);
    }
    void draw(){
        glPushMatrix();
    	glTranslatef(pos.x,pos.y,pos.z);
        cout<<pos<<endl<<scale<<endl;
    	// glRotatef(??,rot.x,rot.y,rot.z);
        glScalef(scale.x,scale.y,scale.z);
        onDraw();
        for(auto i:children)
            i->draw();
        glPopMatrix();
    }
    virtual void onDraw()=0;
};