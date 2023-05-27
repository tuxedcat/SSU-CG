#include "GameObject.h"
#include "Sphere.h"
#include "Cube.h"

// Camera position and rotation
GLfloat camX = 0.0, camY = 0.0, camZ = 5.0;
GLfloat camRotY = 0.0, camRotX = 0.0;
int tick = 0;

GameObject* root;

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
	
	glEnable(GL_TEXTURE_2D);
	root->draw();

	// arm_l
	// glPushMatrix();
	// glTranslatef(1.25,-0.75,0);
	// {
	// 	glTranslatef(0,+1.5,0);
	// 	float angle = sin(tick/100.f)*45;
	// 	glRotatef(angle, 1.0, 0.0, 0.0);
	// 	glTranslatef(0,-1.5,0);
	// }
	// glScalef(0.5,4,0.5);
	// glutSolidCube(1);
	// glPopMatrix();

	// arm_r
	// glPushMatrix();
	// glTranslatef(-1.25,-0.75,0);
	// {
	// 	glTranslatef(0,+1.5,0);
	// 	float angle = -sin(tick/100.f)*45;
	// 	glRotatef(angle, 1.0, 0.0, 0.0);
	// 	glTranslatef(0,-1.5,0);
	// }
	// glScalef(0.5,4,0.5);
	// glutSolidCube(1);
	// glPopMatrix();

	// leg_l
	// glPushMatrix();
	// glTranslatef(0.75,-5,0);
	// {
	// 	glTranslatef(0,+1.5,0);
	// 	float angle = -sin(tick/100.f)*45;
	// 	glRotatef(angle, 1.0, 0.0, 0.0);
	// 	glTranslatef(0,-1.5,0);
	// }
	// glScalef(0.5,4,0.5);
	// glutSolidCube(1);
	// glPopMatrix();
	
	// leg_r
	// glPushMatrix();
	// glTranslatef(-0.75,-5,0);
	// {
	// 	glTranslatef(0,+1.5,0);
	// 	float angle = sin(tick/100.f)*45;
	// 	glRotatef(angle, 1.0, 0.0, 0.0);
	// 	glTranslatef(0,-1.5,0);
	// }
	// glScalef(0.5,4,0.5);
	// glutSolidCube(1);
	// glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("SSUCG");

	// Set up callbacks
	glutDisplayFunc(display);
	glutReshapeFunc([](int w,int h){
			// Set viewport to cover entire window
			glViewport(0, 0, (GLsizei)w, (GLsizei)h);

			// Set projection matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);

			// Reset modelview matrix
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		
	});
	glutIdleFunc([](){
		tick++;
		glutPostRedisplay();
	});
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		switch (key) {
			case 'w':
				camX -= 0.1 * sin(camRotY * PI / 180.0);
				camZ -= 0.1 * cos(camRotY * PI / 180.0);

				// camZ += 0.1 * cos(camRotX * PI / 180.0);
				camY += 0.1 * sin(camRotX * PI / 180.0);
				break;
			case 's':
				camX += 0.1 * sin(camRotY * PI / 180.0);
				camZ += 0.1 * cos(camRotY * PI / 180.0);

				// camZ -= 0.1 * cos(camRotX * PI / 180.0);
				camY -= 0.1 * sin(camRotX * PI / 180.0);
				break;
			case 'a':
				camX += 0.1 * sin((camRotY - 90.0) * PI / 180.0);
				camZ += 0.1 * cos((camRotY - 90.0) * PI / 180.0);
				break;
			case 'd':
				camX -= 0.1 * sin((camRotY - 90.0) * PI / 180.0);
				camZ -= 0.1 * cos((camRotY - 90.0) * PI / 180.0);
				break;
			case 27: // ESC = Quit
				exit(0);
				break;
		}
	});
	glutMotionFunc([](int x, int y) {
		static int px=0, py=0;
		if(abs(x-px)+abs(y-py)<100){//heuristic
			camRotY += 0.1*(x-px);
			if (camRotY > 360.0)
				camRotY -= 360.0;
			if (camRotY < 0.0)
				camRotY += 360.0;
			
			camRotX += 0.1*(y-py);
			if (camRotX > 90.0)
				camRotX = 90.0;
			if (camRotX < -90.0)
				camRotX = -90.0;
		}
		px=x,py=y;
	});

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

	root = new GameObject{};

	auto body = new Cube("body.jpg");
	body->pos.y=-1;
	body->scale={2,4,1};
	root->adopt(body);

	auto body_rescale=new GameObject();
	body_rescale->scale={0.5,0.25,1};
	body->adopt(body_rescale);

	auto head = new Sphere("head.jpg");
	head->pos.y = 3;
	body_rescale->adopt(head);

	auto arm_l = new Cube("arm.jpg");
	arm_l->pos={1.25,0,0};
	arm_l->scale={0.5,4,0.5};
	body_rescale->adopt(arm_l);

	auto arm_r = new Cube("arm.jpg");
	arm_r->pos={-1.25,0,0};
	arm_r->scale={0.5,4,0.5};
	body_rescale->adopt(arm_r);

	auto leg_l = new Cube("leg.jpg");
	leg_l->pos={0.65,-4,0};
	leg_l->scale={0.5,4,0.5};
	body_rescale->adopt(leg_l);

	auto leg_r = new Cube("leg.jpg");
	leg_r->pos={-0.65,-4,0};
	leg_r->scale={0.5,4,0.5};
	body_rescale->adopt(leg_r);

	glutMainLoop();

	return 0;
}