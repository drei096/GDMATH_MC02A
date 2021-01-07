#include<iostream>
#include<cmath>
#include"Quaternion.h"
using namespace std;

void Quaternion::setQuaternion(float wVal, float xVal, float yVal, float zVal)
{
	w = wVal;
	x = xVal;
	y = yVal;
	z = zVal;
}
float Quaternion::getQuaternionValue(char compo)
{
	if (compo == 'w')
		return w;
	if (compo == 'x')
		return x;
	if (compo == 'y')
		return y;
	if (compo == 'z')
		return z;
}
/*
Quaternion normalize(Quaternion q)
{
	float px, py, pz, pw, mag;
	Quaternion q2;
	px = q.getQuaternionValue('x');
	py = q.getQuaternionValue('y');
	pz = q.getQuaternionValue('z');
	pw = q.getQuaternionValue('w');

	mag = sqrt((px * px) + (py * py) + (pz * pz));
	px = px / mag;
	py = py / mag;
	pz = pz / mag;
	pw = pw / mag;
	q2.setQuaternion(pw, px, py, pz);
	return q2;
}
*/
Quaternion Quaternion::multiplyQuaternion(Quaternion q1, Quaternion q2)
{
	float x1, x2, y1, y2, z1, z2, w1, w2, prodX, prodY, prodZ, prodW;
	Quaternion product;
	x1 = q1.getQuaternionValue('x');
	y1 = q1.getQuaternionValue('y');
	z1 = q1.getQuaternionValue('z');
	w1 = q1.getQuaternionValue('w');
	x2 = q2.getQuaternionValue('x');
	y2 = q2.getQuaternionValue('y');
	z2 = q2.getQuaternionValue('z');
	w2 = q2.getQuaternionValue('w');

	prodW = (w1 * w2) - (x1 * x2) - (y1 * y2) - (z1 * z2);
	prodX = (w1 * x2) + (x1 * w2) + (y1 * z2) - (z1 * y2);
	prodY = (w1 * y2) - (x1 * z2) - (y1 * w2) - (z1 * x2);
	prodZ = (w1 * z2) - (x1 * y2) - (y1 * x2) - (z1 * w2);

	product.setQuaternion(prodW, prodX, prodY, prodZ);
	return product;
}