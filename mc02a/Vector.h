#pragma once
#include<iostream>
using namespace std;
class Vector
{
public:
	float vMatrix[4];
public:
	Vector(float x, float y, float z)
	{
		vMatrix[0] = x;
		vMatrix[1] = y;
		vMatrix[2] = z;
		vMatrix[3] = 1;
	}
	void forceZero(int rowIndex)
	{
		if (rowIndex <= 2)
			vMatrix[3] = 0;
		else
			vMatrix[3] = 1;
	}
	void displayVector()
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			cout << i << ":" << vMatrix[i] << endl;
		}
	}
	Vector getRow(Matrix m, int rowIndex)
	{
		float x, y, z;
		x = m.getIndexVal(rowIndex, 0);
		y = m.getIndexVal(rowIndex, 1);
		z = m.getIndexVal(rowIndex, 2);
		//a = m.getIndexVal(rowIndex, 3);
		Vector row(x, y, z);
		row.setVectorVals(x, 0);
		row.setVectorVals(y, 1);
		row.setVectorVals(z, 2);
		//if(rowIndex < 3)
			//row.forceZero(rowIndex);
		//row.setVectorVals(a, 3);
		//row.displayVector();
		return row;
	}
	Vector getColumn(Matrix m, int colIndex)
	{
		float x, y, z;
		x = m.getIndexVal(0, colIndex);
		y = m.getIndexVal(1, colIndex);
		z = m.getIndexVal(2, colIndex);
		//a = m.getIndexVal(3, colIndex);
		Vector column(x, y, z); 
		column.setVectorVals(x, 0);
		column.setVectorVals(y, 1);
		column.setVectorVals(z, 2);
		//if(colIndex < 3)
			//row.forceZero(colIndex);
		//row.setVectorVals(a, 3);
		return column;
	}
	void setVectorVals(float val, int index)
	{
		vMatrix[index] = val;
		//vMatrix[3] = 1;
	}
	float getVectorValue(int index)
	{
		return vMatrix[index];
	}
};

