#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display();
void drawBoard();
void drawEdges();
void drawBlackBoxes();
void drawColorBoxes(float red, float green, float blue);
void createMenu();

int menu_id;
int menu_window;
int menu_value;


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Checkerboard");

	createMenu();
	glutDisplayFunc(display);

	glClearColor(1, 1, 1, 0);
	glColor3f(0, 0, 0);

	glutMainLoop();

	return(0);

}

void menu(int num){
	menu_value = num;
	glutPostRedisplay();
}

void createMenu() {
	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("White", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Orange", 4);
	glutAddMenuEntry("Yellow", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void setWindow(float left, float right, int bottom, int top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	setWindow(0, 800, 0, 600);
	if (menu_value == 0) drawColorBoxes(1, 1, 1);
	if (menu_value == 1) drawColorBoxes(1, 0, 0);
	if (menu_value == 2) drawColorBoxes(0, 1, 0);
	if (menu_value == 3) drawColorBoxes(0, 0, 1);
	if (menu_value == 4) drawColorBoxes(1, .64, 0);
	if (menu_value == 5) drawColorBoxes(1, 1, 0);
	drawBoard();

	glFlush();

}

void drawBoard() {
	drawBlackBoxes();
	drawEdges();
}

void drawEdges() {
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(51, 51);
	glVertex2i(51, 501);
	glVertex2i(501, 501);
	glVertex2i(501, 51);
	glVertex2i(51, 51);
	glEnd();
}

void drawBox(int x, int y) { //lower left coords
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x, y + 50);
	glVertex2i(x + 50,  y + 50);
	glVertex2i(x + 50, y);
	glEnd();
}

void drawBlackBoxes() {
	glColor3f(0, 0, 0);
	for (int iRow = 1; iRow <= 8; iRow = iRow + 2) {
		for (int iCol = 1; iCol <= 8; iCol = iCol + 2) {
			drawBox(50 * iRow + 50, 50 * iCol + 50);
		}
	}
	for (int iRow = 0; iRow <= 8; iRow = iRow + 2) {
		for (int iCol = 0; iCol <= 8; iCol = iCol + 2) {
			drawBox(50 * iRow + 50, 50 * iCol + 50);
		}
	}
}

void drawColorBoxes(float red, float green, float blue) {
	glColor3f(red, green, blue);
	for (int iRow = 1; iRow <= 8; iRow = iRow + 2) {
		for (int iCol = 0; iCol <= 8; iCol = iCol + 2) {
			drawBox(50 * iRow + 50, 50 * iCol + 50);
		}
	}
	for (int iRow = 0; iRow <= 8; iRow = iRow + 2) {
		for (int iCol = 1; iCol <= 8; iCol = iCol + 2) {
			drawBox(50 * iRow + 50, 50 * iCol + 50);
		}
	}
}


