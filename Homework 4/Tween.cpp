#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <fstream>

#define MOVEMENT 10

void display();
void moveDinoUp();
void moveDinoDown();
void moveDinoLeft();
void moveDinoRight();

int offsetX = 0;
int offsetY = 0;

void drawPolyLineFile(const char * fileName) {

	std::ifstream inStream;
	inStream.open(fileName);	// open the file

	if(inStream.fail()) return;
	glClear(GL_COLOR_BUFFER_BIT);      // clear the screen 

	GLint numpolys, numLines;
	GLfloat x, y;
	inStream >> numpolys;		           // read the number of polylines

	for(int iPoly = 0; iPoly < numpolys; iPoly++) { // read each polyline
		inStream >> numLines;
		glBegin(GL_LINE_STRIP);	     // draw the next polyline
		for(int i = 0; i < numLines; i++) {
			inStream >> x >> y;        // read the next x, y pair
			glVertex2f(x + offsetX, 480- y + offsetY);
		}
		glFlush();
		glEnd();
	}
	glFlush();
	inStream.close();
}

void keyboardListener(unsigned char key, int mouseX, int mouseY) {
	switch(key) {
		case 'u':
		case 'U':
			offsetY += MOVEMENT;
			break;
		case 'd':
		case 'D':
			offsetY -= MOVEMENT;
			break;
		case 'r':
		case 'R':
			offsetX += MOVEMENT;
			break;
		case 'l':
		case 'L':
			offsetX -= MOVEMENT;
			break;
		default:
			break;
	}

	drawPolyLineFile("mu.dat");
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("MU Tween");

	glutKeyboardFunc(keyboardListener);
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

	setWindow(0, 1024.0, 0, 768.0);
	drawPolyLineFile("u.dat");

	glFlush();

}

void moveDinoUp() {

}