
#include "sdl_arch.h"
#include "camera.h"

#include <conio.h>

Scene scn;		// the scene object
Camera camera;	// the camera object

float screenWidth = 640, screenHeight = 480;

float R = screenWidth / screenHeight;  // Global Aspect Ratio


//*****************************************************************************
void myDisplay()
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//Draw SDL file
	scn.drawSceneOpenGL();

	glFlush();
	glutSwapBuffers();	// added 8/29

}
	
//*****************************************************************************
void setViewport( int left, int right, int bottom, int top )
{
	glViewport( left, bottom, right - left, top - bottom );
}

//*****************************************************************************
void myReshape( GLsizei W, GLsizei H )
{
	if( R > W/H )
		setViewport( 0, W, 0, W/R );
	else
		setViewport( 0, H * R, 0, H );
}


//*****************************************************************************
void main( int argc, char** argv )
{	
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );

	glutInitWindowSize( 640, 480 );

	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "SDL Chair" );
	glutDisplayFunc( myDisplay );


	glShadeModel( GL_SMOOTH );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );

	glViewport( 0, 0, 640, 480 );

	camera.set( 1.5, 1.5, 1.5, 0, -0.25, 0, 0, 1, 0 );
	camera.setShape( 30.0f, 64.0f/48.0f, 0.5f, 110.0f );		// added for camera use
	//Using SDL to create object
	scn.read( "CHAIR.DAT" );
	glEnable( GL_LIGHTING );
	scn.makeLightsOpenGL();

	glutMainLoop();
}



