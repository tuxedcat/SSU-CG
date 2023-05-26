#pragma once
#include "GameObject.h"

class Cube: public GameObject{
private:
    void onDraw() override{
        // glutSolidCube(1);

        glBegin(GL_QUADS);

        // Front face
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, 0.5);

        // Back face
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.5, -0.5, -0.5);

        // Top face
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, -0.5);

        // Bottom face
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);

        // Right face
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.5, -0.5, 0.5);

        // Left face
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.5, 0.5, -0.5);

        glEnd();
    }
};