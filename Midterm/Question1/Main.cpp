#include <fstream>
#include <iostream>

typedef struct {
	float x;
	float y;
	float z;
}Point;

int length = 0; //total number of points

/* reads an input file consisting of 3d vertices */
Point* readInput() {

	std::ifstream inStream;
	inStream.open("test.dat");	// open the file
	if(inStream.fail()) return NULL;

	float x, y, z;
	inStream >> length;		           // read the number of vertices
	Point *points = new Point[length];

	for(int i = 0; i < length; i++) {
		inStream >> x >> y >> z;        // read the next x, y, z pair
		points[i] = Point { x, y, z };
	}
	inStream.close();
	return points;
}

/*
Calculate if the polygon is planar. A planar polygon can be defined as a polygon where the angle between the two vertices next to it is less than 180 degrees.
We can calculate the angle by calculating acos((p1 dot p2)/(mag(p1)mag(p2)) and converting to degrees
*/
void main() {
	bool planar = true;
	Point* points = readInput();
	for(int i = 0; i < length; i++) {
		Point p = points[i];
		int right = (i == length-1) ?  0 : i+1; //calculate next point
		Point r = points[right];
		float dot = p.x*r.x + p.y*r.y + p.z*r.z; //calc dot product
		float s1 = p.x*p.x + p.y*p.y + p.z*p.z; //magnitude of p1
		float s2 = r.x*r.x + r.y*r.y + r.z*r.z; //magnitude of p2
		float theta = acos(dot / sqrt(s1 * s2)); //theta in radians
		float thetaD = theta * (180 / (atan(1) * 4)); //theta in degrees
		if(thetaD > 180) { 
			planar = false; 
			break;  //break because we already know it's not planar
		}
	}
	std::cout << (planar ? "Planar" : "Non-Planar") << "\n";
	system("PAUSE");
}