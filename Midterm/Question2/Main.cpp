#include <math.h>

float* calcModelMatrix(float x, float y, float z) {
	float modelMatrix[16];
	float a = cos(x);
	float b = sin(x);
	float c = cos(y);
	float d = sin(y);
	float e = cos(z);
	float f = sin(z);

	modelMatrix[0] = c * e;
	modelMatrix[1] = -c * f;
	modelMatrix[2] = -d;
	modelMatrix[3] = 0;

	modelMatrix[4] = (-b * d * e) + (a * f);
	modelMatrix[5] = (b * d* f) + (a * e);
	modelMatrix[6] = -b * c;
	modelMatrix[7] = 0;

	modelMatrix[8] = (a * d * e) + (b * f);
	modelMatrix[9] = (-a * d * f) + (b * e);
	modelMatrix[10] = a * c;
	modelMatrix[11] = 0;

	modelMatrix[12] = 0;
	modelMatrix[13] = 0;
	modelMatrix[14] = 0;
	modelMatrix[15] = 1;
	
	return modelMatrix;
}

float* roll(float x) {
	float rollMatrix[9];
	float a = cos(x);
	float b = sin(x);

	rollMatrix[0] = 1;
	rollMatrix[1] = 0;
	rollMatrix[2] = 0;

	rollMatrix[3] = 0;
	rollMatrix[4] = a;
	rollMatrix[5] = -b;

	rollMatrix[6] = 0;
	rollMatrix[7] = b;
	rollMatrix[8] = a;

	return rollMatrix;
}

float* pitch(float y) {
	float pitchMatrix[9];
	float a = cos(y);
	float b = sin(y);

	pitchMatrix[0] = a;
	pitchMatrix[1] = 0;
	pitchMatrix[2] = -b;

	pitchMatrix[3] = 0;
	pitchMatrix[4] = 1;
	pitchMatrix[5] = 0;

	pitchMatrix[6] = b;
	pitchMatrix[7] = 0;
	pitchMatrix[8] = a;

	return pitchMatrix;
}

float* yaw(float z) {
	float yawMatrix[9];
	float a = cos(z);
	float b = sin(z);

	yawMatrix[0] = a;
	yawMatrix[1] = -b;
	yawMatrix[2] = 0;

	yawMatrix[3] = b;
	yawMatrix[4] = a;
	yawMatrix[5] = 0;

	yawMatrix[6] = 0;
	yawMatrix[7] = 0;
	yawMatrix[8] = 1;

	return yawMatrix;
}