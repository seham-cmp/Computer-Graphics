#include <windows.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct {
	GLfloat x;
	GLfloat y;
} Point;

void display();
void drawRandomHouse();
void drawHouse(GLfloat width, GLfloat height, Point roof);

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Random Village");

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

	setWindow(0, WIDTH, 0, HEIGHT);
	srand(time(NULL));
	int numberOfHouses = 3 + rand() % 12;
	for(int i = 1; i <= numberOfHouses; i++) {
		int randomX = rand() % 120;
		int randomY = rand() % 80;
		glViewport(i * randomX, i * randomY, randomX * 3, randomY * 3);
		drawRandomHouse();
	}

	glFlush();

}

void drawRandomHouse() {
	GLfloat houseWidth = WIDTH / 3;
	GLfloat houseHeight = HEIGHT / 3;
	Point roofPoint; roofPoint.x = houseWidth; roofPoint.y = (houseHeight + houseHeight);
	glColor3f(((double)rand() / RAND_MAX), ((double)rand() / RAND_MAX), ((double)rand() / RAND_MAX));
	drawHouse(houseWidth, houseHeight, roofPoint);
}

void drawEdges(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight) {
	glBegin(GL_LINE_STRIP);
	glVertex2f(bottomLeft.x, bottomLeft.y);
	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(topRight.x, topRight.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glVertex2f(bottomLeft.x, bottomLeft.y);
	glEnd();
}

void drawRoof(Point topLeft, Point topRight, Point roof) {
	glBegin(GL_LINE_STRIP);
	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(roof.x, roof.y);
	glVertex2f(topRight.x, topRight.y);
	glEnd();
}

void drawDoor(Point bottomLeft, Point bottomRight, GLfloat height) {
	GLfloat center = ((bottomLeft.x + bottomRight.x) / 2);
	GLfloat doorOffset = ((bottomLeft.x + bottomRight.x) / 20); //10% of width
	glBegin(GL_LINE_STRIP);
	glVertex2f(center + doorOffset, bottomLeft.y);
	glVertex2f(center - doorOffset, bottomLeft.y);
	glVertex2f(center - doorOffset, height);
	glVertex2f(center + doorOffset, height);
	glVertex2f(center + doorOffset, bottomLeft.y);
	glEnd();
}

void drawWindow(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight) {
	GLfloat tenOffset = ((bottomLeft.x + bottomRight.x) / 7); 
	GLfloat thirtyOffset = ((bottomLeft.x + bottomRight.x) / 20); 
	topLeft.x = topRight.x - thirtyOffset; topLeft.y = topRight.y - thirtyOffset;
	bottomLeft.x = topRight.x - thirtyOffset; bottomLeft.y = topRight.y - tenOffset;
	bottomRight.x = topRight.x - tenOffset; bottomRight.y = topRight.y - tenOffset;
	topRight.x = topRight.x - tenOffset; topRight.y = topRight.y - thirtyOffset;

	drawEdges(bottomLeft, topLeft, topRight, bottomRight);
}

void drawHouse(GLfloat width, GLfloat height, Point roof) {
	Point bottomLeft = { width / 2, height / 2 };
	Point topLeft = { width / 2, height / 2 + height };
	Point topRight = { width / 2 + width, height / 2 + height };
	Point bottomRight = { width / 2 + width, height / 2 };

	drawEdges(bottomLeft, topLeft, topRight, bottomRight);
	drawRoof(topLeft, topRight, roof);
	drawDoor(bottomLeft, bottomRight, height);
	drawWindow(bottomLeft, topLeft, topRight, bottomRight);
}
