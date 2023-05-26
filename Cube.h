#pragma once
#include "GameObject.h"

class Cube: public GameObject{
public:
    Cube(const string& img_path){
        int width, height, channels;
        unsigned char* image = stbi_load(img_path.c_str(), &width, &height, &channels, STBI_rgb);
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);
    }
private:
    GLuint textureID;
    void onDraw() override{
    	glBindTexture(GL_TEXTURE_2D, textureID);
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