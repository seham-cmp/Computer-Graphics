// Sandy Hill, November 19, 1999 for ECE660 
// a Camera class – partial implementation - for flying through 3D scenes. 
#include "SDL_arch.h" 
#include "camera.h" 

bool DEBUG = false;

//<<<<<<<<<<<<<<<<<<<<<<< default constructor >>>>>>>>>>>>>>>>> 
Camera :: Camera(void) 
{ // make default camera 
    setDefaultCamera(); // good default values here 
} 
//<<<<<<<<<<<<<<<<<<<<<<< default constructor >>>>>>>>>>>>>>>>> 
void Camera :: setDefaultCamera(void) 
{ // make default camera 

	if( DEBUG )
		cout << "Calling setDefaultCamera\n";

    setShape(45.0f, 640/(float)480, 0.1f, 200.0f); // good default values here 
	
	Point3 eyePoint = Point3( 10.0, 0.0, 0.0 );
	Point3 lookPoint = Point3( 0.0, 0.0, 0.0 );
	Vector3 upVector = Vector3( 0, 1, 0 );

	set( eyePoint, lookPoint, upVector );

    //set(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0); 
} 
//<<<<<<<<<<<<<<<<<<<< set >>>>>>>>>>>>>>>>>>> 
void Camera :: set( float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ )
{
	if( DEBUG )
		cout << "Calling set\n";

	Point3 Eye = Point3( eyeX, eyeY, eyeZ );
	Point3 look = Point3( lookX, lookY, lookZ );

	Vector3 up = Vector3( upX, upY, upZ );

    eye.set(Eye); 
    n.set(eye.x - look.x, eye.y - look.y,eye.z - look.z); 
    u.set(up.cross(n)); 
    v.set(n.cross(u)); 
    u.normalize(); v.normalize(); n.normalize(); 
    setModelViewMatrix(); 	


}

//<<<<<<<<<<<<<<<<<<<< set >>>>>>>>>>>>>>>>>>> 
void Camera :: set(Point3 Eye, Point3 look, Vector3 up) 
{ // make u, v, n vectors 

	if( DEBUG )
		cout << "Calling set\n";

    eye.set(Eye); 
    n.set(eye.x - look.x, eye.y - look.y,eye.z - look.z); 
    u.set(up.cross(n)); 
    v.set(n.cross(u)); 
    u.normalize(); v.normalize(); n.normalize(); 
    setModelViewMatrix(); 
} 
//<<<<<<<<<<<<<<<< setModelViewMatrix >>>>>>>>>>>>>>>> 
void Camera :: setModelViewMatrix(void) 
{ // load modelview matrix with existing camera values 

	if( DEBUG )
		cout << "Calling setModelViewMatrix\n";

    float m[16]; 
    Vector3 eVec(eye.x, eye.y, eye.z); 
    m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eVec.dot(u); 
    m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eVec.dot(v); 
    m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -eVec.dot(n); 
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1.0; 
    glMatrixMode(GL_MODELVIEW); 
    glLoadMatrixf(m); 
} 
//<<<<<<<<<<<<<<<<<<<<<<< setShape >>>>>>>>>>>>>>>> 
void Camera :: setShape(float vAngle, float asp, float nr, float fr) 
{ // load projection matrix and camera values 

	if( DEBUG )
		cout << "Calling setShape, vAngle: " << vAngle << ", asp: " << asp << ", nr: " << nr << ", fr: " << fr << "\n";

    viewAngle = vAngle; 
    aspect = asp; 
    nearDist = nr; 
    farDist = fr; 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(viewAngle, aspect, nearDist, farDist); 
    glMatrixMode(GL_MODELVIEW); // set its mode back again 
} 
//<<<<<<<<<<<<<<<<<<<<<<<<<<<< setAspect >>>>>>>>>>>>>>>>>>>>>> 
void Camera:: setAspect(float asp) 
{ 
	if( DEBUG )
		cout << "Calling setAspect\n";
	
	aspect = asp;
} 
//<<<<<<<<<<<<<<<<<<<<<<< getShape >>>>>>>>>>>>>>>> 
void Camera :: getShape(float& vAngle, float& asp, float& nr, float& fr) 
{ 
	if( DEBUG )
		cout << "Calling getShape\n";

    vAngle = viewAngle; 
    asp = aspect; 
    nr = nearDist; 
    fr = farDist; 
} 
