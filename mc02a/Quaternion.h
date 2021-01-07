#pragma once
#include<iostream>
using namespace std;

class Quaternion
{
private:
	float w, x, y, z;
public:
	void setQuaternion(float wVal, float xVal, float yVal, float zVal);
	float getQuaternionValue(char compo);
	Quaternion multiplyQuaternion(Quaternion q1, Quaternion q2);
};

