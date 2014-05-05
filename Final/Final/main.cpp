#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <string>
#include <vector>
#include "RGBpixmap.h"

RGBpixmap pix[6];
double xAngle = 0; double yAngle = 0;
struct Vector3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

std::vector<Vector3> vertices;
std::vector<Vector3> normals;

void createVectors() {
	vertices.push_back({ 0, 0, 0 });
	vertices.push_back({ 1, 0, 0 });
	vertices.push_back({ 1, 1, 0 });
	vertices.push_back({ .5, 1.5, 0 });
	vertices.push_back({ 0, 1, 0 });
	vertices.push_back({ 0, 0, 1 });
	vertices.push_back({ 1, 0, 1 });
	vertices.push_back({ 1, 1, 1 });
	vertices.push_back({ .5, 1.5, 1 });
	vertices.push_back({ 0, 1, 1 });
}

void createNormals() {
	normals.push_back({ -1, 0, 0 });
	normals.push_back({ -.707, -.707, 0 });
	normals.push_back({ .707, .707, 0 });
	normals.push_back({ 1, 0, 0 });
	normals.push_back({ 0, -1, 0 });
	normals.push_back({ 0, 0, 1 });
	normals.push_back({ 0, 0, -1 });
}

void drawQuads() {

	//left face
	int norm = 0;
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(1.0, 0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glTexCoord2f(1.0, 1.0);  glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[9].x, vertices[9].y, vertices[9].z);
	glTexCoord2f(0, 1.0);  glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glEnd();

	//roof left face
	norm = 1;
	glBindTexture(GL_TEXTURE_2D, 2003);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1.0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(0, 0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glTexCoord2f(1.0, 0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[9].x, vertices[9].y, vertices[9].z);
	glTexCoord2f(1.0, 1.0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[8].x, vertices[8].y, vertices[8].z);
	glEnd();

	//roof right face
	norm = 2;
	glBindTexture(GL_TEXTURE_2D, 2003);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glTexCoord2f(1.0, 1.0);  glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(0, 1.0);	 glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[8].x, vertices[8].y, vertices[8].z);
	glTexCoord2f(0, 0);		glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glEnd();

	//right face
	norm = 3;
	glBindTexture(GL_TEXTURE_2D, 2004);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glTexCoord2f(1.0, 1.0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glTexCoord2f(0, 1.0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glTexCoord2f(0, 0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glEnd();

	//bottom face
	norm = 4;
	glBindTexture(GL_TEXTURE_2D, 2005);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(0, 1.0); glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glTexCoord2f(1.0, 1.0);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glTexCoord2f(1.0, 0);		glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glEnd();
}

void drawPolygons() {
	//front of barn
	int norm = 5;
	glBindTexture(GL_TEXTURE_2D, 2002);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);		glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glTexCoord2f(1.0, 0);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glTexCoord2f(1.0, .5);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
	glTexCoord2f(.5, .75);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[8].x, vertices[8].y, vertices[8].z);
	glTexCoord2f(0, .5);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[9].x, vertices[9].y, vertices[9].z);
	glEnd();

	//back of barn
	norm = 6;
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glTexCoord2f(1.0, .5);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glTexCoord2f(.5, .75);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glTexCoord2f(0, .5);	glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glTexCoord2f(0, 0);		glNormal3f(normals[norm].x, normals[norm].y, normals[norm].z); glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	glRotated(xAngle, 1, 0, 0); glRotated(yAngle, 0, 1, 0);

	drawQuads();
	drawPolygons();
	
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	pix[0].readBMPFile("side.bmp");        	// make pixmap procedurally 
	pix[0].setTexture(2001);              	// create texture

	pix[1].readBMPFile("door.bmp");  // make pixmap from image
	pix[1].setTexture(2002);		// create texture

	pix[2].readBMPFile("roof.bmp");  // make pixmap from image
	pix[2].setTexture(2003);		// create texture

	pix[0].readBMPFile("side_window.bmp");        	// make pixmap procedurally 
	pix[0].setTexture(2004);              	// create texture

	pix[0].readBMPFile("dirt.bmp");        	// make pixmap procedurally 
	pix[0].setTexture(2005);              	// create texture

	glViewport(0, 0, 640, 480); // set up the viewing system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 640.0 / 480, 1.0, 30.0); // set camera shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, -0.2, -4); // move camera back
}
void spin() {
	yAngle -= .01; //xAngle += .01;
	display();
}

void main(int argc, char **argv) {
	createVectors();
	createNormals();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Problem 2");
	glutDisplayFunc(display);
	
	init();
	glutIdleFunc(spin);
	glutMainLoop();
}