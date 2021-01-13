#pragma once
#include<iostream>
using namespace std;
class Vector
{
public:
	float vMatrix[4];
public:
	Vector(float x, float y, float z) //VECTOR CREATION
	{
		vMatrix[0] = x;
		vMatrix[1] = y;
		vMatrix[2] = z;
		vMatrix[3] = 1;
	}
	void forceZero(int rowIndex) //to set index column 3 as <0,0,0,1>
	{
		if (rowIndex <= 2)
			vMatrix[3] = 0;
		else
			vMatrix[3] = 1;
	}
	void displayVector() //DISPLAY VECTOR
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			cout << i << ":" << vMatrix[i] << endl;
		}
	}
	Vector getRow(Matrix m, int rowIndex) //for getting row values; returns row vector values
	{
		float x, y, z;
		x = m.getIndexVal(rowIndex, 0);
		y = m.getIndexVal(rowIndex, 1);
		z = m.getIndexVal(rowIndex, 2);
		Vector row(x, y, z);
		row.setVectorVals(x, 0);
		row.setVectorVals(y, 1);
		row.setVectorVals(z, 2);
		return row;
	}
	Vector getColumn(Matrix m, int colIndex) //for getting column values; returns column vector values
	{
		float x, y, z;
		x = m.getIndexVal(0, colIndex);
		y = m.getIndexVal(1, colIndex);
		z = m.getIndexVal(2, colIndex);
		Vector column(x, y, z); 
		column.setVectorVals(x, 0);
		column.setVectorVals(y, 1);
		column.setVectorVals(z, 2);
		return column;
	}
	void setVectorVals(float val, int index) //index refers to position and val refers to the value to be applied or changed
	{
		vMatrix[index] = val;
	}
	float getVectorValue(int index) //get specific value in a vector using index parameters
	{
		return vMatrix[index];
	}
};

