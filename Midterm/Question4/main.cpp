#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define RATIO 1.618033989

GLfloat x1, x2, y1, y2;
bool rotate = false;

//draws a rectangle using the global coordinates
void drawRectangle() {
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
		glVertex2f(x1, y1);
	glEnd();
}

//finds the largest starting rectangle using the window width/height
void findFirstRectangle() {
	x1 = 0; y1 = 0;
	x2 = glutGet(GLUT_WINDOW_WIDTH);
	y2 = glutGet(GLUT_WINDOW_HEIGHT);
	if(x2 / y2 < RATIO) y2 = x2 / RATIO;
	else x2 = y2*RATIO;
	drawRectangle();
}

//calculates the next rectangle switching between horizontal and vertical boxes
void drawRectangles() {
	if(rotate) x2 = y2 / RATIO;
	else y2 = x2 / RATIO;
	rotate = !rotate;
	drawRectangle();
}

void setWindow(float left, float right, int bottom, int top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	setWindow(0, 600, 0, 400);

	findFirstRectangle();
	while(abs((long)x1 - (long)x2) > 1 && abs((long)y1 - (long)y2) > 1) { //keep going until the boxes are less than 1 pixel differences
		drawRectangles();
	}
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Golden Ratio");

	glutDisplayFunc(display);
	glutMainLoop();
}