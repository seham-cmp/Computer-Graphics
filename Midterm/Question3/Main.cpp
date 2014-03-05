#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.141592653

double angle;

typedef struct {
	GLdouble x;
	GLdouble y;
}Point;

Point rotate(Point a, double angle, double length) {
	Point p;
	p.x = length * cos(angle) + a.x;
	p.y = length * sin(angle) + a.y;
	return p;
}

double distance(Point a, Point b) {
	double x2 = a.x * b.x;
	double y2 = a.y * b.y;
	return sqrt(x2 + y2);
}

void drawSnowflake(Point first, Point second, int level) {
	double length = distance(first, second);
	if(level == 0) {
		glBegin(GL_LINE_STRIP);
		glVertex2d(first.x, first.y);
		glVertex2d(second.x, second.y);
		glEnd();
	}
	else {

		Point p1 = rotate(first, angle, length);
		drawSnowflake(first, p1, level - 1);
		angle += PI / 3.0;

		Point p2 = rotate(first, angle, length);
		drawSnowflake(p1, p2, level - 1);
		angle -= PI * (2.0 / 3.0);

		Point p3 = rotate(first, angle, length);
		drawSnowflake(p2, p3, level - 1);
		angle += PI / 3.0;

		drawSnowflake(p3, second, level - 1);
	}
}

void setWindow(float left, float right, int bottom, int top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	setWindow(0, 640, 0, 480);
	Point a = {160.0, 40.0};
	Point b = {480.0, 40.0};
	Point c = {320.0, 450.0};
	angle = PI;
	drawSnowflake(b, a, 1);
	angle = PI / 3.0;
	drawSnowflake(a, c, 1);
	angle = PI * 5 / 3;
	drawSnowflake(c, b, 1);

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Koch Snowflake");

	glutDisplayFunc(display);
	glutMainLoop();

	return(0);

}