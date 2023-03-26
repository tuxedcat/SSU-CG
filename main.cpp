#include <GL/glut.h>
#include <cmath>

// Cube vertices
GLfloat vertices[][3] = {
  {-1.0,-1.0,-1.0},
  {1.0,-1.0,-1.0},
  {1.0,1.0,-1.0},
  {-1.0,1.0,-1.0},
  {-1.0,-1.0,1.0},
  {1.0,-1.0,1.0},
  {1.0,1.0,1.0},
  {-1.0,1.0,1.0}
};

// Cube edges
GLubyte edges[][2] = {
  {0,1},
  {1,2},
  {2,3},
  {3,0},
  {4,5},
  {5,6},
  {6,7},
  {7,4},
  {0,4},
  {1,5},
  {2,6},
  {3,7}
};

// Camera position and rotation
GLfloat camX = 0.0, camY = 0.0, camZ = 5.0;
GLfloat camYaw = 0.0, camPitch = 0.0;

void display() {
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Reset modelview matrix
  glLoadIdentity();
  
  // Apply camera transformation
  glTranslatef(-camX, -camY, -camZ);
  glRotatef(-camPitch, 1.0, 0.0, 0.0);
  glRotatef(-camYaw, 0.0, 1.0, 0.0);
  
  // Draw cube edges
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  for (int i = 0; i < 12; i++) {
    glVertex3fv(vertices[edges[i][0]]);
    glVertex3fv(vertices[edges[i][1]]);
  }
  glEnd();
  
  // Swap buffers
  glutSwapBuffers();
}

void reshape(int w, int h) {
  // Set viewport to cover entire window
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
  // Set projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
  
  // Reset modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void idle() {
  // Rotate cube
  static GLfloat angle = 0.0;
  angle += 0.5;
  if (angle > 360.0) {
    angle -= 360.0;
  }
  glRotatef(angle, 0.0, 1.0, 0.0);
  
  // Redraw
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    // Camera movement
    case 'w':
      camX -= 0.1 * sin(camYaw * 3.14159265358979323846 / 180.0);
      camZ += 0.1 * cos(camYaw * 3.14159265358979323846 / 180.0);
      break;
    case 's':
      camX += 0.1 * sin(camYaw * 3.14159265358979323846 / 180.0);
      camZ -= 0.1 * cos(camYaw * 3.14159265358979323846 / 180.0);
      break;
    case 'a':
      camX -= 0.1 * sin((camYaw - 90.0) * 3.14159265358979323846 / 180.0);
      camZ += 0.1 * cos((camYaw - 90.0) * 3.14159265358979323846 / 180.0);
      break;
    case 'd':
      camX += 0.1 * sin((camYaw - 90.0) * 3.14159265358979323846 / 180.0);
      camZ -= 0.1 * cos((camYaw - 90.0) * 3.14159265358979323846 / 180.0);
      break;
      
    // Camera rotation
    case 'q':
      camYaw += 2.0;
      if (camYaw > 360.0) {
        camYaw -= 360.0;
      }
      break;
    case 'e':
      camYaw -= 2.0;
      if (camYaw < 0.0) {
        camYaw += 360.0;
      }
      break;
    case 'r':
      camPitch += 2.0;
      if (camPitch > 90.0) {
        camPitch = 90.0;
      }
      break;
    case 'f':
      camPitch -= 2.0;
      if (camPitch < -90.0) {
        camPitch = -90.0;
      }
      break;
      
    // Quit
    case 27:  // ESC key
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