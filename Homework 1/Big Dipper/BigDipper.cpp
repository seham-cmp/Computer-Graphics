#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display();
void drawStars();
void connectTheDots();


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Big Dipper");

	glutDisplayFunc(display);
	glutMainLoop();

	return(0);

}

void setWindow(float left, float right, int bottom, int top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	setWindow(0, 640.0, 0, 480.0);
	drawStars();		
	connectTheDots();

	glFlush();

}

void drawStars() {
	glPointSize(10); //make points bigger
	glBegin(GL_POINTS);
	glVertex2i(82, 480 - 182);
	glVertex2i(214, 480 - 177);
	glVertex2i(284, 480 - 228);
	glVertex2i(373, 480 - 286);
	glVertex2i(381, 480 - 374);
	glVertex2i(536, 480 - 400);
	glVertex2i(574, 480 - 303);
	glEnd();
}

void connectTheDots() {
	glBegin(GL_LINE_STRIP);
	glVertex2i(82, 480 - 182);
	glVertex2i(214, 480 - 177);
	glVertex2i(284, 480 - 228);
	glVertex2i(373, 480 - 286);
	glVertex2i(381, 480 - 374);
	glVertex2i(536, 480 - 400);
	glVertex2i(574, 480 - 303);
	glVertex2i(373, 480 - 286);
	glEnd();
}
