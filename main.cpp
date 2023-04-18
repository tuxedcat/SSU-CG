#include <stdio.h>
#include <GL/glut.h>
#include <cmath>

const double PI = 3.14159265358979323846;

// Camera position and rotation
GLfloat camX = 0.0, camY = 0.0, camZ = 5.0;
GLfloat camRotY = 0.0, camRotX = 0.0;
int tick = 0;

void display()
{
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset modelview matrix
  glLoadIdentity();

  // Apply camera transformation
  glRotatef(-camRotX, 1.0, 0.0, 0.0);
  glRotatef(-camRotY, 0.0, 1.0, 0.0);
  glTranslatef(-camX, -camY, -camZ);

  // glBegin(GL_TRIANGLES);
  // glColor3f(0.1, 0.2, 0.3);
  // glVertex3f(0, 0, 0);
  // glVertex3f(1, 0, 0);
  // glVertex3f(0, 1, 0);
  // glEnd();

  // glPushMatrix();
  // glRotatef(tick%360, 0.0, 1.0, 0.0);
  // glutSolidCube(1);
  // glPopMatrix();

  glPushMatrix();
  glTranslatef(0,2,0);
  glutSolidSphere(1, 10, 10);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-0.3,2,0.9);
  glutSolidSphere(0.1, 5, 5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.3,2,0.9);
  glutSolidSphere(0.1, 5, 5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,-1,0);
  glScalef(2,4,2);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.25,-0.75,0);
  {
    glTranslatef(0,+1.5,0);
    float angle = sin(tick/100.f)*45;
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0,-1.5,0);
  }
  glScalef(0.5,4,0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1.25,-0.75,0);
  {
    glTranslatef(0,+1.5,0);
    float angle = -sin(tick/100.f)*45;
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0,-1.5,0);
  }
  glScalef(0.5,4,0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.75,-5,0);
  {
    glTranslatef(0,+1.5,0);
    float angle = -sin(tick/100.f)*45;
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0,-1.5,0);
  }
  glScalef(0.5,4,0.5);
  glutSolidCube(1);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-0.75,-5,0);
  {
    glTranslatef(0,+1.5,0);
    float angle = sin(tick/100.f)*45;
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0,-1.5,0);
  }
  glScalef(0.5,4,0.5);
  glutSolidCube(1);
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
  tick++;
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      camX += 0.1 * sin(camRotY * PI / 180.0);
      camZ -= 0.1 * cos(camRotY * PI / 180.0);
      break;
    case 's':
      camX -= 0.1 * sin(camRotY * PI / 180.0);
      camZ += 0.1 * cos(camRotY * PI / 180.0);
      break;
    case 'a':
      camX += 0.1 * sin((camRotY - 90.0) * PI / 180.0);
      camZ -= 0.1 * cos((camRotY - 90.0) * PI / 180.0);
      break;
    case 'd':
      camX -= 0.1 * sin((camRotY - 90.0) * PI / 180.0);
      camZ += 0.1 * cos((camRotY - 90.0) * PI / 180.0);
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
  glutInitWindowSize(1280, 720);
  glutCreateWindow("SSUCG");

  // Set up callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);

  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  glClearColor (0.0, 0.5, 0.5, 0.0);
  glShadeModel (GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  // Start main loop
  glutMainLoop();

  return 0;
}