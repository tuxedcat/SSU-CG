#include <stdio.h>
#include <GL/glut.h>
#include <cmath>

const double PI = 3.14159265358979323846;

GLfloat cubevtx[][3] = {
    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0}};
GLubyte cubeedg[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

// Camera position and rotation
GLfloat camX = 0.0, camY = 0.0, camZ = 5.0;
GLfloat camRotY = 0.0, camRotX = 0.0;
GLfloat cubeRotY = 0;

void display()
{
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset modelview matrix
  glLoadIdentity();

  // Apply camera transformation
  glTranslatef(-camX, -camY, -camZ);
  glRotatef(-camRotX, 1.0, 0.0, 0.0);
  glRotatef(-camRotY, 0.0, 1.0, 0.0);

  // Draw cube edges
  glPushMatrix();
  glRotatef(cubeRotY, 0.0, 1.0, 0.0);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  for (int i = 0; i < 12; i++) {
    glVertex3fv(cubevtx[cubeedg[i][0]]);
    glVertex3fv(cubevtx[cubeedg[i][1]]);
  }
  glEnd();
  glPopMatrix();

  // Swap buffers
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  // Set viewport to cover entire window
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  // Set projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);

  // Reset modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void idle()
{
  cubeRotY += 0.5;
  if (cubeRotY > 360.0) {
    cubeRotY -= 360.0;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      camX -= 0.1 * sin(camRotY * PI / 180.0);
      camZ += 0.1 * cos(camRotY * PI / 180.0);
      break;
    case 's':
      camX += 0.1 * sin(camRotY * PI / 180.0);
      camZ -= 0.1 * cos(camRotY * PI / 180.0);
      break;
    case 'a':
      camX -= 0.1 * sin((camRotY - 90.0) * PI / 180.0);
      camZ += 0.1 * cos((camRotY - 90.0) * PI / 180.0);
      break;
    case 'd':
      camX += 0.1 * sin((camRotY - 90.0) * PI / 180.0);
      camZ -= 0.1 * cos((camRotY - 90.0) * PI / 180.0);
      break;
    case 'q':
      camRotY += 2.0;
      if (camRotY > 360.0) {
        camRotY -= 360.0;
      }
      break;
    case 'e':
      camRotY -= 2.0;
      if (camRotY < 0.0) {
        camRotY += 360.0;
      }
      break;
    case 'r':
      camRotX += 2.0;
      if (camRotX > 90.0) {
        camRotX = 90.0;
      }
      break;
    case 'f':
      camRotX -= 2.0;
      if (camRotX < -90.0) {
        camRotX = -90.0;
      }
      break;
    // ESC = Quit
    case 27:
      exit(0);
      break;
  }
}

int main(int argc, char** argv) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow("OpenGL Cube");

  // Set up callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);

  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  // Start main loop
  glutMainLoop();

  return 0;
}