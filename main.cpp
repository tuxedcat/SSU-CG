#include "GameObject.h"
#include "Sphere.h"

GLuint textureID;

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

	auto head = new Sphere();
	head->pos.y = 2;
	root->adopt(head);

	auto eye_r = new Sphere();
	eye_r->pos = {-0.3,2,0.9};
	eye_r->scale = {0.1, 0.1, 0.1};
	root->adopt(eye_r);

	auto eye_l = new Sphere();
	eye_l->pos = {0.3,2,0.9};
	eye_l->scale = {0.1, 0.1, 0.1};
	root->adopt(eye_l);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	root->draw();

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

	//Texture Test
	glPushMatrix();
	glScalef(5,5,5);

	glBegin(GL_QUADS);//GL_TRIANGLES
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1, -1, 0.0);
	glTexCoord2f(1, 0.0);
	glVertex3f(1, -1, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0.0);
	glTexCoord2f(0.0, 1);
	glVertex3f(-1, 1, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glFlush();
	glPopMatrix();

	// Swap buffers
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
				break;
			case 's':
				camX += 0.1 * sin(camRotY * PI / 180.0);
				camZ += 0.1 * cos(camRotY * PI / 180.0);
				break;
			case 'a':
				camX += 0.1 * sin((camRotY - 90.0) * PI / 180.0);
				camZ += 0.1 * cos((camRotY - 90.0) * PI / 180.0);
				break;
			case 'd':
				camX -= 0.1 * sin((camRotY - 90.0) * PI / 180.0);
				camZ -= 0.1 * cos((camRotY - 90.0) * PI / 180.0);
				break;
			// ESC = Quit
			case 27:
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

	// Load texture
	int width, height, channels;
	unsigned char* image = stbi_load("texture.jpg", &width, &height, &channels, STBI_rgb);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);

	root = new GameObject{};

	// Start main loop
	glutMainLoop();

	return 0;
}