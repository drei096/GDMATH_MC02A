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

		iden3d.setIndexVal(0, 3, x);
		iden3d.setIndexVal(1, 3, y);
		iden3d.setIndexVal(2, 3, z);
		
		return iden3d;
	}
	Matrix getScaleMatrix(float sx, float sy, float sz)
	{
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();
		

		iden3d.setIndexVal(0, 0, sx);
		iden3d.setIndexVal(1, 1, sy);
		iden3d.setIndexVal(2, 2, sz);
		
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

	Matrix multiplyMatrix(Matrix m1, Matrix m2, bool ism2Coord) //multiplies 2 4x4 matrices
	{
		Transformations transf;
		int rowIndex, colIndex, k=0, i, j;
		float dprod;
		float matrixtest[4][4];
		Matrix productMatrix(matrixtest);
		productMatrix.get3DIdentity();

		for (rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			for (colIndex = 0; colIndex < 4; colIndex++)
			{
				Vector dummyV(1, 2, 3);
				Vector dummyV2(2, 3, 4);

				if (rowIndex == 3)
				{
					dummyV.setVectorVals(0, 0);
					dummyV.setVectorVals(0, 1);
					dummyV.setVectorVals(0, 2);
					dummyV.setVectorVals(1, 3);
				}
				else
				{
					dummyV.setVectorVals(m1.getIndexVal(rowIndex, 0), 0);
					dummyV.setVectorVals(m1.getIndexVal(rowIndex, 1), 1);
					dummyV.setVectorVals(m1.getIndexVal(rowIndex, 2), 2);
					dummyV.setVectorVals(m1.getIndexVal(rowIndex, 3), 3);
				}

				dummyV2 = dummyV2.getColumn(m2, colIndex);
				if(ism2Coord == true)
					dummyV2.setVectorVals(1, 3);
				else
				{
					if(colIndex == 3)
						dummyV2.setVectorVals(1, 3);
					else
					{
						dummyV2.setVectorVals(0, 3);
					}
				}

				dprod = transf.dotProd(dummyV, dummyV2);
				productMatrix.setIndexVal(rowIndex, colIndex, dprod);
			}
		}
		return productMatrix;
	}

	Matrix getRotateQuaternions(float theta, float x, float y, float z)
	{
		float mat[4][4], normU, qx,qy,qz,qw;
		Matrix iden3d(mat);
		
		iden3d.get3DIdentity();

		//normalizing axis vector
		normU = sqrt((x * x) + (y * y) + (z * z));
		qx = x / normU;
		qy = y / normU;
		qz = z / normU;

		//quaternion q setup
		qw = cos(theta / 2);
		qx = qx * sin(theta / 2);
		qy = qy * sin(theta / 2);
		qz = qz * sin(theta / 2);
		
		//set the rotation matrix

		iden3d.setIndexVal(0, 0, (qw*qw) + (qx*qx) - (qy*qy) - (qz*qz));
		iden3d.setIndexVal(0, 1, (2 * qx * qy) - (2 * qw * qz));
		iden3d.setIndexVal(0, 2, (2 * qx * qz) + (2 * qw * qy));
		iden3d.setIndexVal(0, 3, 0);

		iden3d.setIndexVal(1, 0, (2 * qx * qy) + (2 * qw * qz));
		iden3d.setIndexVal(1, 1, (qw * qw) - (qx * qx) + (qy * qy) - (qz * qz));
		iden3d.setIndexVal(1, 2, (2 * qy * qz) - (2 * qw * qx));
		iden3d.setIndexVal(1, 3, 0);

		iden3d.setIndexVal(2, 0, (2 * qx * qz) - (2 * qw * qy));
		iden3d.setIndexVal(2, 1, (2 * qy * qz) + (2 * qw * qx));
		iden3d.setIndexVal(2, 2, (qw * qw) - (qx * qx) - (qy * qy) + (qz * qz));
		iden3d.setIndexVal(2, 3, 0);

		return iden3d;
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

		iden3d.setIndexVal(0, 0, 1/sqx);
		iden3d.setIndexVal(1, 1, sqy);
		iden3d.setIndexVal(2, 2, sqz/sqz);
		iden3d.displayMatrix(); //display
		return iden3d;
	}
	
	Matrix project(int choice)
	{
		float m1[4][4] = {
		{1.0,0.0,0.0,0.0},
		{0.0,1.0,0.0,0.0},
		{0.0,0.0,0.0,1.0},
		{0.0,0.0,0.0,0.0}
		};

		float m2[4][4] = {
		{1,0,0,0},
		{0,0,0,0},
		{0,0,1,0},
		{0,0,0,1}
		};

		float m3[4][4] = {
		{0,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
		};

		Matrix projectXY(m1);
		Matrix projectXZ(m2);
		Matrix projectYZ(m3);

		if (choice == 1)
			return projectXY;
		if (choice == 2)
			return projectXZ;
		if (choice == 3)
			return projectYZ;
	}
};

