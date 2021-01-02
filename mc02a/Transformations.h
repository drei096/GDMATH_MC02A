#pragma once
#include<iostream>
#include<vector>
#define PI 3.141526
using namespace std;

class Transformations
{
public:
	Matrix getTranslateMatrix(float x, float y, float z)
	{
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();
		iden3d.displayMatrix(); //display

		iden3d.setIndexVal(0, 3, x);
		iden3d.setIndexVal(1, 3, y);
		iden3d.setIndexVal(2, 3, z);
		iden3d.displayMatrix(); //display
		return iden3d;
	}
	Matrix getScaleMatrix(float sx, float sy, float sz)
	{
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();
		iden3d.displayMatrix(); //display

		iden3d.setIndexVal(0, 0, sx);
		iden3d.setIndexVal(1, 1, sy);
		iden3d.setIndexVal(2, 2, sz);
		iden3d.displayMatrix(); //display
		return iden3d;
	}
	float dotProd(Vector v1, Vector v2)
	{
		float sum = 0;
		int i;
		for (i = 0; i < 4; i++)
		{
			sum = sum + (v1.vMatrix[i] * v2.vMatrix[i]);
		}
		return sum;
	}
	Matrix multiplyMatrix(Matrix m1, Matrix m2) //multiplies 2 4x4 matrices
	{
		Transformations transf;
		int rowIndex, colIndex;
		float m[4][4], dprod;
		Matrix productMatrix(m);
		for (rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			for (colIndex = 0; colIndex < 4; colIndex++)
			{
				Vector dummyV(1, 2, 3);
				Vector dummyV2(2, 3, 4);
				dummyV = dummyV.getRow(m1, rowIndex);
				dummyV2 = dummyV2.getColumn(m2, colIndex);
				dprod = transf.dotProd(dummyV, dummyV2);
				productMatrix.setIndexVal(rowIndex, colIndex, dprod);
			}
		}
		cout << endl;
		productMatrix.displayMatrix();
		return productMatrix;
	}
	Vector multiplyWithCompo(Matrix c, Vector p)
	{
		Transformations transf;
		int rowIndex;
		float dprod;
		Vector productVector(1,2,3);
		for (rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			Vector dummyV(1, 2, 3);
			dummyV = dummyV.getRow(c, rowIndex);
			dprod = transf.dotProd(dummyV, p);
			productVector.setVectorVals(dprod, rowIndex);
		}
		cout << endl;
		//productVector.displayVector();
		return productVector;
	}
	Matrix getRotateMatrix(float theta, char dir, char axis) //c counterclockwise, l clockwise
	{
		int i, j;
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();
		iden3d.displayMatrix(); //display

		if (dir == 'l')
			theta = -theta;
		theta = theta * (PI / 180.0); //conv to radians

		/* PANG 2D PALA TO HAHAHA AWIT NAMAN FUCK EULER ANGLES
		* may nakita ako implementation by quaternions tho, hanapin ko HAHAHAH
		iden3d.setIndexVal(0, 0, cos(theta));
		iden3d.setIndexVal(1, 1, cos(theta));
		iden3d.setIndexVal(0, 1, -1 * sin(theta));
		iden3d.setIndexVal(1, 0, sin(theta));
		iden3d.displayMatrix(); //display
		return iden3d;
		*/

		//revision
		/*
		//EULER ANGLES
		if (axis == 'x'){
			iden3d.setIndexVal(0, 0, cos(theta));
			iden3d.setIndexVal(1, cos(theta), -1 * sin(theta));
			iden3d.setIndexVal(2, sin(theta), cos(theta));
		}
		if (axis == 'y'){
			iden3d.setIndexVal(cos(theta), 0, -1 * sin(theta));
			iden3d.setIndexVal(1, 1, 1);
			iden3d.setIndexVal(sin(theta), 2, cos(theta));
		}
		if (axis == 'z'){
			iden3d.setIndexVal(cos(theta), -1 * sin(theta), 0);
			iden3d.setIndexVal(sin(theta), cos(theta), 1);
			iden3d.setIndexVal(2, 2, 2);
		}
		iden3d.displayMatrix(); //display
		return iden3d;
		*/

	}
	Matrix getDistortMatrix(char axis, float amt1st, float amt2nd) //amt1st is from axis 1 to axis 2, amt2nd is axis 1 to axis 3
	{
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();
		iden3d.displayMatrix(); //display

		if (axis == 'x')
		{
			iden3d.setIndexVal(0, 1, amt1st);
			iden3d.setIndexVal(0, 2, amt2nd);
		}
		if (axis == 'y')
		{
			iden3d.setIndexVal(1, 0, amt1st);
			iden3d.setIndexVal(1, 2, amt2nd);
			iden3d.setIndexVal(0, 1, 1);
		}
		if (axis == 'z')
		{
			iden3d.setIndexVal(2, 0, amt1st);
			iden3d.setIndexVal(2, 1, amt2nd);
		}
		iden3d.displayMatrix(); //display
		return iden3d;	 
	}
	Matrix getSqueezeMatrix(float sqx, float sqy, float sqz)
	{
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();
		iden3d.displayMatrix(); //display

		iden3d.setIndexVal(0, 0, 1.0/sqx * sqrt(sqy) * sqrt(sqz));
		iden3d.setIndexVal(1, 1, (1.0/sqy)*sqrt(sqx)*sqrt(sqz));
		iden3d.setIndexVal(2, 2, 1.0/sqz * sqrt(sqx) * sqrt(sqy));
		iden3d.displayMatrix(); //display
		return iden3d;
	}
	Matrix composeTransform(Matrix mc, Matrix mt)
	{
		Transformations transf;
		float mat[4][4];
		Matrix newCompo(mat);
		newCompo = transf.multiplyMatrix(mc, mt);
		return newCompo;
	}
	
};

