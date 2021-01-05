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
		//iden3d.displayMatrix(); //display

		iden3d.setIndexVal(0, 3, x);
		iden3d.setIndexVal(1, 3, y);
		iden3d.setIndexVal(2, 3, z);
		//iden3d.displayMatrix(); //display
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
				 //HAHAHAHA eto na pala yun yung hahanapin sa 3rd column
				
				cout << "dummy v1:" << endl;
				dummyV.displayVector();

				dummyV2 = dummyV2.getColumn(m2, colIndex);
				if(ism2Coord == true)
					dummyV2.setVectorVals(1, 3);//m2.getIndexVal(colIndex, 3), 3);
				else
				{
					if(colIndex == 3)
						dummyV2.setVectorVals(1, 3);
					else
					{
						dummyV2.setVectorVals(0, 3);
					}
				}

				cout << "dummy v2:" << endl;
				dummyV2.displayVector();

				dprod = transf.dotProd(dummyV, dummyV2);
				productMatrix.setIndexVal(rowIndex, colIndex, dprod);
			}
		}
		//cout << endl;
		//productMatrix.displayMatrix();
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
		//cout << endl;
		//productVector.displayVector();
		return productVector;
	}
	Matrix getRotateMatrix(float theta, char axis, bool isInverse) //c counterclockwise, l clockwise
	{
		int i, j;
		float mat[4][4];
		Matrix iden3d(mat);
		Matrix m1(mat);
		Matrix m2(mat);
		Matrix m3(mat);
		m1.get3DIdentity();
		m2.get3DIdentity();
		m3.get3DIdentity();

		//EULER ANGLES
		if (isInverse == false)
		{
			if (axis == 'x')
			{
				m1.setIndexVal(0, 0, 1);
				m1.setIndexVal(1, 1, cos(theta));
				m1.setIndexVal(2, 2, cos(theta));
				m1.setIndexVal(1, 2, sin(theta));
				m1.setIndexVal(2, 1, -1 * sin(theta));
				return m1;
			}
			if (axis == 'y')
			{
				m2.setIndexVal(1, 1, 1);
				m2.setIndexVal(0, 0, cos(theta));
				m2.setIndexVal(2, 2, cos(theta));
				m2.setIndexVal(2, 0, -1 * sin(theta));
				m2.setIndexVal(0, 2, sin(theta));
				return m2;
			}
			if (axis == 'z')
			{
				m3.setIndexVal(0, 0, cos(theta));
				m3.setIndexVal(1, 1, cos(theta));
				m3.setIndexVal(0, 1, sin(theta));
				m3.setIndexVal(1, 0, -1 * sin(theta));
				m3.setIndexVal(2, 2, 1);
				return m3;
			}
		}
		else
		{
			if (axis == 'x')
			{
				m1.setIndexVal(0, 0, 1);
				m1.setIndexVal(1, 1, cos(theta));
				m1.setIndexVal(2, 2, cos(theta));
				m1.setIndexVal(1, 2, -1 * sin(theta));
				m1.setIndexVal(2, 1,  sin(theta));
				return m1;
			}
			if (axis == 'y')
			{
				m2.setIndexVal(1, 1, 1);
				m2.setIndexVal(0, 0, cos(theta));
				m2.setIndexVal(2, 2, cos(theta));
				m2.setIndexVal(2, 0, -1 * sin(theta));
				m2.setIndexVal(0, 2, sin(theta));
				return m2;
			}
			if (axis == 'z')
			{
				m3.setIndexVal(0, 0, cos(theta));
				m3.setIndexVal(1, 1, cos(theta));
				m3.setIndexVal(0, 1, -1 * sin(theta));
				m3.setIndexVal(1, 0, sin(theta));
				m3.setIndexVal(2, 2, 1);
				return m3;
			}
		}
	}

	//pacheck nito
	Matrix getRotateQuaternions(float theta, float x, float y, float z)
	{
		float mat[4][4];
		Matrix iden3d(mat);
		float normU;

		normU = sqrt((x * x) + (y * y) + (z * z));
		x = x / normU;
		y = y / normU;
		z = z / normU;

		//diagonal
		iden3d.setIndexVal(0, 0, (cos(theta / 2) * cos(theta / 2)) + ((sin(theta / 2) * x) * (sin(theta / 2) * x)) - ((sin(theta / 2) * y) * (sin(theta / 2) * y)) - ((sin(theta / 2) * z) * (sin(theta / 2) * z)));
		iden3d.setIndexVal(1, 1, (cos(theta / 2) * cos(theta / 2)) - ((sin(theta / 2) * x) * (sin(theta / 2) * x)) + ((sin(theta / 2) * y) * (sin(theta / 2) * y)) - ((sin(theta / 2) * z) * (sin(theta / 2) * z)));
		iden3d.setIndexVal(2, 2, (cos(theta / 2) * cos(theta / 2)) - ((sin(theta / 2) * x) * (sin(theta / 2) * x)) - ((sin(theta / 2) * y) * (sin(theta / 2) * y)) + ((sin(theta / 2) * z) * (sin(theta / 2) * z)));
		//1st row
		iden3d.setIndexVal(0, 1, (2 * (sin(theta / 2) * x) * (sin(theta / 2) * y)) - (2 * (cos(theta / 2)) * (sin(theta / 2) * z)));
		iden3d.setIndexVal(0, 2, (2 * (sin(theta / 2) * x) * (sin(theta / 2) * z)) + (2 * (cos(theta / 2)) * (sin(theta / 2) * y)));
		//2nd row
		iden3d.setIndexVal(1, 0, (2 * (sin(theta / 2) * x) * (sin(theta / 2) * y)) + (2 * (cos(theta / 2)) * (sin(theta / 2) * z)));
		iden3d.setIndexVal(1, 2, (2 * (sin(theta / 2) * y) * (sin(theta / 2) * z)) - (2 * (cos(theta / 2)) * (sin(theta / 2) * x)));
		//3rd row
		iden3d.setIndexVal(2, 0, (2 * (sin(theta / 2) * x) * (sin(theta / 2) * y)) - (2 * (cos(theta / 2)) * (sin(theta / 2) * z)));
		iden3d.setIndexVal(2, 1, (2 * (sin(theta / 2) * y) * (sin(theta / 2) * z)) + (2 * (cos(theta / 2)) * (sin(theta / 2) * x)));

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
		newCompo = transf.multiplyMatrix(mc, mt, false);
		return newCompo;
	}
	Matrix getRotateArbitrary(float theta, float x, float y, float z)
	{
		float mat[4][4];
		Matrix iden3d(mat);
		iden3d.get3DIdentity();

		
		iden3d.setIndexVal(0, 0, (x*x) * (1 - cos(theta)) + cos(theta));
		iden3d.setIndexVal(1, 0, x * y * (1 - cos(theta)) - (z * sin(theta)));
		iden3d.setIndexVal(2, 0, x * z * (1 - cos(theta)) + (y * sin(theta)));

		iden3d.setIndexVal(0, 1, x * y * (1 - cos(theta)) + (z * sin(theta)));
		iden3d.setIndexVal(1, 1, (y*y) * (1 - cos(theta)) + cos(theta));
		iden3d.setIndexVal(2, 1, y * z * (1 - cos(theta)) - (x * sin(theta)));

		iden3d.setIndexVal(0, 2, z * x * (1 - cos(theta)) - (y * sin(theta)));
		iden3d.setIndexVal(1, 2, z * y * (1 - cos(theta)) + (x * sin(theta)));
		iden3d.setIndexVal(2, 2, (z*z) * (1 - cos(theta)) + cos(theta));
		return iden3d;
		
	}
	float normalize(float px, float py, float pz)
	{
		return sqrt((px * px) + (py * py) + (pz * pz));
	}
};

