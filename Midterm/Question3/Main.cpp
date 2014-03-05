#include <GL/glut.h>
#include <math.h>

#define LEVELS 5

/*swaps location of two float vectors*/
void swap(GLfloat * a, GLfloat * b) {
	GLfloat temp = *a;
	*a = *b;
	*b = temp;
}

void divideLineSegment(GLfloat *a, GLfloat *b, int level) {
	GLfloat newTriangle[2][2]; //base of new triangle
	GLfloat slope[2]; //slope to the new point
	GLfloat midpoint[2]; //midpoint of the given line
	GLfloat newPoint[2]; //vertex of the new triangle
	if(level > 0) {
		int j;
		GLfloat ratio = sqrt(3.0); //triangle ratio 1:sqrt(3)

		/* all points must form another equalateral triangle to be valid */
		/* find midpoint of line. used to determine the extruded point */
		for(j = 0; j < 2; j++) midpoint[j] = a[j] + (b[j] - a[j]) / 2.0;
		
		/* find point 1/3 of line. used as base of triangle */
		for(j = 0; j < 2; j++) newTriangle[0][j] = a[j] + (b[j] - a[j]) / 3.0;
		
		/* find point 2/3 of line. used as base of triangle */
		for(j = 0; j < 2; j++) newTriangle[1][j] = a[j] + (b[j] - a[j]) / 3.0 * 2.0;

		/* find the slope vector */
		for(j = 0; j < 2; j++) slope[j] = (midpoint[j] - newTriangle[0][j]);
		
		/* need to switch these slopes to obtain an outward normal vector */
		swap(&slope[0], &slope[1]); 
		slope[0] = -slope[0];

		/* put it all together to get the x,y coordinate of the new point*/
		for(j = 0; j < 2; j++) newPoint[j] = midpoint[j] + ratio * slope[j];

		/* make recursive calls using this new triangle until the total depth level has been met */
		divideLineSegment(a, newTriangle[0], level - 1); //first pt to the 1/3 mark
		divideLineSegment(newTriangle[0], newPoint, level - 1); // 1/3 mark to the new pt
		divideLineSegment(newPoint, newTriangle[1], level - 1); // new pt to the 2/3 mark
		divideLineSegment(newTriangle[1], b, level - 1); // 2/3 mark to the second pt
	}
	else { //max level reached, draw the two points
		glVertex2fv(a);
		glVertex2fv(b);
	}
}

void drawSnowflake(GLfloat *a, GLfloat *b, GLfloat *c, int n) {
	divideLineSegment(a, b, n);
	divideLineSegment(b, c, n);
	divideLineSegment(c, a, n);
}

void display() {
	/* kock snowflake only works with equalateral triangles so we create one */
	GLfloat side = 50;
	GLfloat xstart = 20.0;
	GLfloat ystart = 25.0;
	GLfloat v[3][2] = { { xstart, ystart }, { xstart + side / 2.0, ystart + side / 2.0*sqrt(3.0) }, { xstart + side, ystart } };
	
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINES); //each point creates a vertex so we only need to init drawing once
	drawSnowflake(v[0], v[1], v[2], LEVELS);
	glEnd();
	glFlush();
}

void setWindow() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 100, 0.0, 100);
	glMatrixMode(GL_MODELVIEW);
}

/*set up glut stuff */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Koch snowflake");
	glutDisplayFunc(display);
	setWindow();
	glutMainLoop();
}
