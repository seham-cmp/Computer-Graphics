#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <fstream>

#define RATIO 1.777          //Width/height ratio 1920/1080
#define deltat .1	         //increment of t

int windowWidth;             
int windowHeight;             
float tween = 0;

typedef struct {
	GLfloat x;
	GLfloat y;
}Point;

Point* loadPolyLineFile(const char * fileName) {

	std::ifstream inStream;
	inStream.open(fileName);	// open the file
	if(inStream.fail()) return NULL;

	GLint numpolys, numLines;
	GLfloat x, y;
	inStream >> numpolys;		           // read the number of polylines
	Point polyLine[12];

	for(int iPoly = 0; iPoly < numpolys; iPoly++) { // read each polyline
		inStream >> numLines;
		for(int i = 0; i < numLines; i++) {
			inStream >> x >> y;        // read the next x, y pair
			polyLine[i] = Point { x, y };
		}
	}
	inStream.close();
	return polyLine;
}

void keyboardListener(unsigned char key, int mouseX, int mouseY) {
	switch(key) {
		case 'm':
		case 'M':
			if(tween > 0.1) tween -= deltat;
			break;
		case 'u':
		case 'U':
			if(tween < 1) tween += deltat;
			break;
		default:
			break;
	}
}

void drawTween(Point start[], Point end[], int indices, float t) {
	//rainbow colors
	GLfloat tweenShape[12][2];

	for(int pt = 0; pt < indices; pt++) {
		tweenShape[pt][0] = (1.0 - t) * start[pt].x + t * end[pt].x;
		tweenShape[pt][1] = 480 - ((1.0 - t) * start[pt].y + t * end[pt].y);
	}
	glColor3f(0, 0, 1.0);
	glVertexPointer(2, GL_FLOAT, 0, tweenShape);
	//glColorPointer(3, GL_FLOAT, 0, VertexColors);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_LINE_LOOP, 0, 12);

	glutSwapBuffers();
	glutPostRedisplay();
}

void display() {
	Point* shape = loadPolyLineFile("m.dat");
	Point mShape[12];
	for(int i = 0; i < 12; i++) {
		mShape[i] = shape[i];
	}
	shape = loadPolyLineFile("u.dat");
	Point uShape[12];
	for(int i = 0; i < 12; i++) {
		uShape[i] = shape[i];
	}

	drawTween(mShape, uShape, 12, tween);
}

//sets window size to be relative to screen size
void initWindow() {
	windowWidth = (int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.8);
	windowHeight = (int)(windowWidth / RATIO);

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.1), (glutGet((GLenum)GLUT_SCREEN_HEIGHT) / 2) - (windowHeight / 2));
	glutCreateWindow("MU Tween");
}

void initGl() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-windowWidth / 2, windowWidth, -windowHeight/2, windowHeight);
	glMatrixMode(GL_MODELVIEW);

	glEnableClientState(GL_VERTEX_ARRAY);  //enable a vertex array
	//glEnableClientState(GL_COLOR_ARRAY);  //enable color array
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, windowWidth, windowHeight);
}

void initListeners() {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardListener);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	initWindow();
	initListeners();
	initGl();

	glutMainLoop();

	return(0);
}


