#include <windows.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <fstream>

#define WIDTH 1280
#define HEIGHT 720
#define MOVEMENT 10

typedef struct {
	GLfloat x;
	GLfloat y;
} Point;

void display();
void drawHouse(GLfloat width, GLfloat height, Point roof);

int offsetX = 0;
int offsetY = 0;

int numberOfHouses;
int randomX[12];
int randomY[12];
float randomColor[12][3];

void drawPolyLineFile(const char * fileName) {

	std::ifstream inStream;
	inStream.open(fileName);	// open the file

	if(inStream.fail()) return;

	GLint numpolys, numLines;
	GLfloat x, y;
	inStream >> numpolys;		           // read the number of polylines

	for(int iPoly = 0; iPoly < numpolys; iPoly++) { // read each polyline
		inStream >> numLines;
		glBegin(GL_LINE_STRIP);	     // draw the next polyline
		for(int i = 0; i < numLines; i++) {
			inStream >> x >> y;        // read the next x, y pair
			glVertex2f(x + offsetX, y + offsetY);
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
	display();
}

void defineRandom() {
	srand(time(NULL));
	numberOfHouses = 3 + rand() % 12;
	for(int i = 1; i <= numberOfHouses; i++) {
		randomX[i] = rand() % 120;
		randomY[i] = rand() % 80;
		for(int color = 0; color < 3; color++) {
			randomColor[i][color] = ((double)rand() / RAND_MAX);
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dino Village");
	glutKeyboardFunc(keyboardListener);

	defineRandom();
	glutDisplayFunc(display);
	glutMainLoop();

	return(0);

}


void setWindow(float left, float right, int bottom, int top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void drawDinosaur() {
	glColor3f(1, 1, 1);
	glViewport(0, 0, WIDTH, HEIGHT);
	drawPolyLineFile("dino.dat");
}

void drawRandomHouse(int houseNum) {
	GLfloat houseWidth = WIDTH / 3;
	GLfloat houseHeight = HEIGHT / 3;
	Point roofPoint; roofPoint.x = houseWidth; roofPoint.y = (houseHeight + houseHeight);
	glColor3f(randomColor[houseNum][0], randomColor[houseNum][1], randomColor[houseNum][2]);
	drawHouse(houseWidth, houseHeight, roofPoint);
	glFlush();
}

void drawHouses() {
	for(int i = 1; i <= numberOfHouses; i++) {
		glViewport(i * randomX[i], i * randomY[i], randomX[i] * 3, randomY[i] * 3);
		drawRandomHouse(i);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	setWindow(0, WIDTH, 0, HEIGHT);
	drawHouses();
	drawDinosaur();
	glFlush();
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
