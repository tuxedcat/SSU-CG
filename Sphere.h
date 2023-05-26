#pragma once
#include "GameObject.h"

class Sphere: public GameObject{
public:
    Sphere(const string& img_path){
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
        drawSphere(8, 8);
    }
    void drawSphere(int slices, int stacks)
    {
        for (int i = 0; i < slices; ++i)
        {
            double lat0 = PI * (-0.5 + static_cast<double>(i) / slices);
            double lat1 = PI * (-0.5 + static_cast<double>(i + 1) / slices);
            double y0 = sin(lat0);
            double y1 = sin(lat1);
            double cosLat0 = cos(lat0);
            double cosLat1 = cos(lat1);
            
            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= stacks; ++j)
            {
                double lng = 2 * PI * static_cast<double>(j) / stacks;
                double x = cos(lng);
                double z = sin(lng);
                
                glNormal3f(x * cosLat0, y0, z * cosLat0);
                glTexCoord2f(static_cast<double>(j) / stacks, static_cast<double>(i) / slices);
                glVertex3f(x * cosLat0, y0, z * cosLat0);
                
                glNormal3f(x * cosLat1, y1, z * cosLat1);
                glTexCoord2f(static_cast<double>(j) / stacks, static_cast<double>(i + 1) / slices);
                glVertex3f(x * cosLat1, y1, z * cosLat1);
            }
            glEnd();
        }
    }
};