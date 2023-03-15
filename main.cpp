#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

// Global variables for camera position and direction
float cameraX = 0.0, cameraY = 0.0, cameraZ = 5.0;
float cameraAngleX = 0.0, cameraAngleY = 0.0;

// Global variables for light position and direction
float lightX = 0.0, lightY = 5.0, lightZ = 5.0;
float lightAngleX = -45.0, lightAngleY = 45.0;

// Draw a cube with lighting
void drawCubeWithLight() {
    // Set material properties
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Set light properties
    GLfloat light_position[] = { lightX, lightY, lightZ, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Draw cube
    glutSolidCube(1.0);

    // Disable lighting
    glDisable(GL_LIGHTING);
}

// Display function
void display() {
    // Clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set camera position and direction
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + cos(cameraAngleY * 3.14159 / 180.0), cameraY + sin(cameraAngleX * 3.14159 / 180.0), cameraZ + sin(cameraAngleY * 3.14159 / 180.0), 0.0, 1.0, 0.0);

    // Set light position and direction
    glPushMatrix();
    glRotatef(lightAngleY, 0.0, 1.0, 0.0);
    glRotatef(lightAngleX, 1.0, 0.0, 0.0);
    GLfloat light_position[] = { lightX, lightY, lightZ, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    // Draw cube with lighting
    drawCubeWithLight();
    // Swap buffers
    glutSwapBuffers();
}

// Keyboard function for camera movement
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraX += 0.1 * cos(cameraAngleY * 3.14159 / 180.0);
        cameraZ += 0.1 * sin(cameraAngleY * 3.14159 / 180.0);
        break;
    case 's':
        cameraX -= 0.1 * cos(cameraAngleY * 3.14159 / 180.0);
        cameraZ -= 0.1 * sin(cameraAngleY * 3.14159 / 180.0);
        break;
    case 'a':
        cameraX -= 0.1 * sin(cameraAngleY * 3.14159 / 180.0);
        cameraZ += 0.1 * cos(cameraAngleY * 3.14159 / 180.0);
        break;
    case 'd':
        cameraX += 0.1 * sin(cameraAngleY * 3.14159 / 180.0);
        cameraZ -= 0.1 * cos(cameraAngleY * 3.14159 / 180.0);
        break;
    }
    glutPostRedisplay();
    cout << cameraX << ' ' << cameraY << ' ' << cameraZ << endl;
}

// Special keyboard function for camera rotation
void specialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        cameraAngleX += 5.0;
        break;
    case GLUT_KEY_DOWN:
        cameraAngleX -= 5.0;
        break;
    case GLUT_KEY_LEFT:
        cameraAngleY -= 5.0;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngleY += 5.0;
        break;
    }
    glutPostRedisplay();
}

// Idle function for light rotation
void idle() {
    lightAngleX += 0.5;
    lightAngleY += 0.5;
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL GLUT Camera and Lighting");

    // Set up callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutIdleFunc(idle);

    // Set up OpenGL
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    // Start main loop
    glutMainLoop();

    return 0;
}