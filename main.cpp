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

	// GLfloat light_pos[4]={camX,camY,camZ,0.0};//Light pos = camera pos
	GLfloat light_pos[4]={1,1,1,0};//Light pos = absolute
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	
	glEnable(GL_TEXTURE_2D);
	root->draw();

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
		root->update();
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
	glClearColor (0.6, 0.85, 1.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
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

	auto neck = new Cube("skin.jpg");
	neck->pos.y = 2.5;
	body_rescale->adopt(neck);

	auto head = new Sphere("head.jpg");
	head->pos.y = 3;
	body_rescale->adopt(head);

	auto arm_l_anchor = new GameObject;
	arm_l_anchor->onUpdate=[arm_l_anchor](){
		arm_l_anchor->rot.x=sin(tick/100.f)*45;
	};
	arm_l_anchor->pos={0,2,0};
	body_rescale->adopt(arm_l_anchor);
	
	auto arm_l = new Cube("arm.jpg");
	arm_l->pos={1.25,-2,0};
	arm_l->scale={0.5,4,0.5};
	arm_l_anchor->adopt(arm_l);

	auto arm_r_anchor = new GameObject;
	arm_r_anchor->onUpdate=[arm_r_anchor](){
		arm_r_anchor->rot.x=-sin(tick/100.f)*45;
	};
	arm_r_anchor->pos={0,2,0};
	body_rescale->adopt(arm_r_anchor);

	auto arm_r = new Cube("arm.jpg");
	arm_r->pos={-1.25,-2,0};
	arm_r->scale={0.5,4,0.5};
	arm_r_anchor->adopt(arm_r);

	auto leg_l_anchor = new GameObject;
	leg_l_anchor->onUpdate=[leg_l_anchor](){
		leg_l_anchor->rot.x=-sin(tick/100.f)*45;
	};
	leg_l_anchor->pos={0,-2,0};
	body_rescale->adopt(leg_l_anchor);

	auto leg_l = new Cube("leg.jpg");
	leg_l->pos={0.65,-2,0};
	leg_l->scale={0.5,4,0.5};
	leg_l_anchor->adopt(leg_l);

	auto leg_r_anchor = new GameObject;
	leg_r_anchor->onUpdate=[leg_r_anchor](){
		leg_r_anchor->rot.x=sin(tick/100.f)*45;
	};
	leg_r_anchor->pos={0,-2,0};
	body_rescale->adopt(leg_r_anchor);

	auto leg_r = new Cube("leg.jpg");
	leg_r->pos={-0.65,-2,0};
	leg_r->scale={0.5,4,0.5};
	leg_r_anchor->adopt(leg_r);

	auto land = new Cube("land.jpg");
	land->pos={0,-7,0};
	land->scale={100,0.2,100};
	root->adopt(land);

	glutMainLoop();

	return 0;
}