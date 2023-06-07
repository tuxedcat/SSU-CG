#pragma once
#include "Core.h"
#include "Vec3.h"

class GameObject{
public:
    set<GameObject*> children;
    Vec3 pos;
    Vec3 rot;
    Vec3 scale;
    function<void()> onUpdate=[](){};
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
        glRotatef(rot.z,0,0,1);
        glRotatef(rot.y,0,1,0);
        glRotatef(rot.x,1,0,0);
        glScalef(scale.x,scale.y,scale.z);
        onDraw();
        for(auto i:children)
            i->draw();
        glPopMatrix();
    }
    virtual void onDraw(){};
    void update(){
        onUpdate();
        for(auto i:children)
            i->update();
    }
};