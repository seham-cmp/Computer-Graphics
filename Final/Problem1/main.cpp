#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include "SDL\SDL_arch.h"
#include "SDL\camera.h"

Camera cam; 

void keyboardListener(unsigned char key, int mouseX, int mouseY) {
	switch(key) {
		case 'd':
		case 'D':
			cam.slide(-.2, 0, 0); //right
			break;
		case 'a':
		case 'A':
			cam.slide(.2, 0, 0); //left
			break;
		case 'w':
		case 'W':
			cam.slide(0, -.2, 0); //up
			break;
		case 's':
		case 'S':
			cam.slide(0, .2, 0); //down
			break;
		case 'i':
		case 'I':
			cam.slide(0, 0, 0.2); //zoom in
			break;
		case 'k':
		case 'K':
			cam.slide(0, 0, -0.2); //zoom out
			break; 

		case 'j':
		case 'J':
			cam.roll(3.0);
			break;
		case 'l':
		case 'L':
			cam.roll(-3.0);
			break;
		case 'q':
		case 'Q':
			cam.pitch(-3.0); 
			cam.slide(0, -.3, 0); //up
			break;
		case 'e':
		case 'E':
			cam.pitch(3.0);
			cam.slide(0, .3, 0); //down
			break;
		case 'u':
		case 'U':
			cam.yaw(3.0);
			cam.slide(-.3, 0, 0); //right
			break;
		case 'o':
		case 'O':
			cam.yaw(-3.0);
			cam.slide(.3, 0, 0); //left
			break;
		case 'r':
		case 'R':
			cam.set(4, 4, 4, 0, 0, 0, 0, 1, 0); // reset camera
			break;
	}
	glutPostRedisplay(); // draws it again
}
void drawSdlObject() {
	glPushMatrix();
	glTranslated(0.3, 0.42, 0.65);
	Scene scn;
	scn.read("sdl.dat");
	scn.drawSceneOpenGL();
	glPopMatrix();
}

void setSurface() {
	// set properties of the surface material
	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // gray
	GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// set the light source properties
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat light_position[] = { 2.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	// set the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 1.0; // half-height of the window
	glOrtho(-winHt * 64 / 48.0, winHt * 64 / 48.0, -winHt, winHt, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3, 1.3, 2, 0, 0.25, 0, 0.0, 1.0, 0.0);
	cam.set(4, 4, 4, 0, 0, 0, 0, 1, 0); // make the initial camera
	cam.setShape(30.0f, 64.0f / 48.0f, 0.5f, 50.0f);
}

//<<<<<<<<<<<<<<<<<<<<< displaySolid >>>>>>>>>>>>>>>>>>>>>>
void displaySolid(void)
{
	// start drawing
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
	drawSdlObject();
	glFlush();
	glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework 6");
	glutKeyboardFunc(keyboardListener);
	glutDisplayFunc(displaySolid);

	glEnable(GL_LIGHTING); // enable the light source
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); // for hidden surface removal
	glEnable(GL_NORMALIZE); // normalize vectors for proper shading

	glClearColor(1,1,1,0.0f); 
	glViewport(0, 0, 640, 480);
	setSurface();

	glutMainLoop();
}