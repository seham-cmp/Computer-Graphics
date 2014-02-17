#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <fstream>

#define RATIO 1.618          //Golden Raito 1:1.618
#define WW    2000            //Width of viewport
#define WH    (WW/RATIO)     //Height of viewport
#define HALFX ((int)(WW/2))  //X coordinate  min/max
#define HALFY ((int)(WH/2))  //Y coordinate  min/max
#define deltat .001	         //increment of t
//Globals
int windowWidth;             //Window width in pixels
int windowHeight;            //Window height in pixels 

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
	
	//drawPolyLineFile("mu.dat");
}

void display() {
	float delta = .01;
	Point* shape = loadPolyLineFile("m.dat");
	Point mShape[12];
	for(int i = 0; i < 12; i++) {
		mShape[i] = shape[i];
	}
	Point* uShape = loadPolyLineFile("u.dat");

	float VertexColors[12][3] = { { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } };
	GLfloat tweenShape[12][2];

	static float tween = 0 - delta;
	if(tween < 1) tween += delta; //increment the tween

	for(int pt = 0; pt < 12; pt++) {
		tweenShape[pt][0] = (1.0 - tween) * mShape[pt].x + tween * uShape[pt].x;
		tweenShape[pt][1] = 480-((1.0 - tween) * mShape[pt].y + tween * uShape[pt].y);
	}

	glVertexPointer(2, GL_FLOAT, 0, tweenShape);
	glColorPointer(3, GL_FLOAT, 0, VertexColors);

	for(int i = 0; i < 1000000; i++);  //lazy man's loop

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_LINE_LOOP, 0, 12);

	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	windowWidth = (int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.8);
	windowHeight = (int)(windowWidth / RATIO);

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((int)(glutGet((GLenum)GLUT_SCREEN_WIDTH)*.1), (glutGet((GLenum)GLUT_SCREEN_HEIGHT) / 2) - (windowHeight / 2));
	glutCreateWindow("MU Tween");

	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-HALFX, HALFX, -HALFY, HALFY);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(1, 1, 1, 1);
	glEnableClientState(GL_VERTEX_ARRAY);  //enable a vertex array
	glEnableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, windowWidth, windowHeight);


	glutMainLoop();
	return(0);
}


