
#include <iostream>
#include <GL/glut.h>
#include<cstdlib>
#include<time.h>


GLfloat theta = 0.0;
GLfloat tmp_theta = 0.0;
GLfloat randoms[40];
GLfloat drop_shift;
void DrawLeaf()
{
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(0.02f, 0.0f, -2.0f);
	glVertex3f(0.035f, 0.015f, -2.0f);
	glVertex3f(0.04f, 0.015f, -2.0f);
	glVertex3f(0.025f, 0.0f, -2.0f);
	glVertex3f(0.04f, 0.0f, -2.0f);
	glVertex3f(0.05f, 0.01f, -2.0f);
	glVertex3f(0.055f, 0.01f, -2.0f);
	glVertex3f(0.045f, 0.0f, -2.0f);
	glVertex3f(0.055f, 0.0f, -2.0f);
	glVertex3f(0.06f, -0.005f, -2.0f);
	glEnd();
}
void DrawSnow(){

	glPushMatrix();

	glRotatef(tmp_theta, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i <= 6; i++) {

	DrawLeaf();
	glScalef(1.0f, -1.0f, 1.0f);
	DrawLeaf();
	glScalef(1.0f, -1.0f, 1.0f);
	glRotatef(60, 0.0f, 0.0f, 1.0f);

	}	
	glPopMatrix();
}



void Initialize() {
	srand(clock());
	glClearColor(0.0, 0.0, 0.0, 0.0); /*Specify the red, green, blue, and alpha values used when the
	   color buffers are cleared*/

	glMatrixMode(GL_PROJECTION); //subsequent matrix operations are on the PROJECTION matrix
	glLoadIdentity();// load the identity matrix for the projection matrix first
	//then set camera projection
	gluPerspective(45.0f, 960.0f / 720.0f, 0.1f, 100.0f); // (angle of view, aspect ratio, near, far clipping planes)

	for (int i = 0; i < 40; i++) {
		randoms[i] =  -0.25+rand() / float(RAND_MAX)/2;
	}
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT); /* clear the color buffer,the buffers enabled for color
						writing*/
						//glScalef(-1.0f,1.0f,1.0f);
						//DrawSnow();




	glColor3f(1.0, 1.0, 1.0);// use white color to draw objects

	glMatrixMode(GL_MODELVIEW); //subsequent matrix operations are on the MODELVIEW matrix
	glLoadIdentity();// load the identity matrix
	tmp_theta = theta;
	glTranslatef(0.0f, -drop_shift, 0.0f);
	//glRotatef(theta, 0.0f, 0.0f, 1.0f);
	
	for (int i = 0; i < 40; i += 2) {
		glTranslatef(randoms[i], randoms[i + 1], 0.0f);
		DrawSnow();
	}

	glFlush();//force execution of GL commands
}

void myIdle()
{
	theta += 0.02;
	if (theta > 360.0)
		theta -= 360.0;
	drop_shift += 0.00005;
	glutPostRedisplay();
}



int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);//initialize glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);/*use single (as opposed to double) buffer
												and RGB (as apposed to INDEX) color*/
	glutInitWindowSize(960, 720); // set window size, (width, height)
	glutInitWindowPosition(0, 0);  // set window position, (0,0) is the top left corner
	glutCreateWindow("POLYGON");//  name the window
	Initialize();
	glutDisplayFunc(Draw);
	glutIdleFunc(&myIdle);
	glutMainLoop();//put the program in an infinite event loop
	return 0;
}