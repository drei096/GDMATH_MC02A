/*needed to be addressed:
* 
* address natin muna yung matrix multiplication fxn tsaka tayo sa rotation
* pwede mo paglaruan yung test calls para makuha mo feel ng fxns
*/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<cctype>
#include"Matrix.h"
#include"Vector.h"
#include"Transformations.h"
#include"Vector2D.h"
using namespace std;

typedef struct point3D
{
	float x;
	float y;
	float z;
};

typedef struct point2D
{
	float x;
	float y;
};

point3D computeBarycenter(vector <point3D> points)
{
	int i;
	float sumX = 0, sumY = 0, sumZ = 0;
	point3D barycenter;
	for (i = 0; i < points.size(); i++)
	{
		sumX = sumX + points[i].x;
		sumY = sumY + points[i].y;
		sumZ = sumZ + points[i].z;
	}
	sumX = sumX / points.size();
	sumY = sumY / points.size();
	sumZ = sumZ / points.size();
	barycenter.x = sumX;
	barycenter.y = sumY;
	barycenter.z = sumZ;
	return barycenter;
}

vector <point3D> projectXY(vector <point3D> points)
{
	int i;
	vector <point3D> projPoints;
	point3D temp;
	Transformations tran;
	Vector resultant(1, 2, 3);
	float mat[4][4] = {
		{1.0,0.0,0.0,0.0},
		{0.0,1.0,0.0,0.0},
		{0.0,0.0,0.0,1.0},
		{0.0,0.0,0.0,0.0}
	};
	Matrix projectMat(mat);
	for (i = 0; i < points.size(); i++)
	{
		Vector dummyPoint(points[i].x, points[i].y, points[i].z);
		resultant = tran.multiplyWithCompo(projectMat, dummyPoint);
		temp.x = resultant.getVectorValue(0);
		temp.y = resultant.getVectorValue(1);
		temp.z = resultant.getVectorValue(2);
		projPoints.push_back(temp);
	}
	return projPoints;
}

vector <point3D> projectXZ(vector <point3D> points)
{
	int i;
	vector <point3D> projPoints;
	point3D temp;
	Transformations tran;
	Vector resultant(1, 2, 3);
	float mat[4][4] = {
		{1,0,0,0},
		{0,0,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	Matrix projectMat(mat);
	for (i = 0; i < points.size(); i++)
	{
		Vector dummyPoint(points[i].x, points[i].y, points[i].z);
		resultant = tran.multiplyWithCompo(projectMat, dummyPoint);
		temp.x = resultant.getVectorValue(0);
		temp.y = resultant.getVectorValue(1);
		temp.z = resultant.getVectorValue(2);
		projPoints.push_back(temp);
	}
	return projPoints;
}

vector <point3D> projectYZ(vector <point3D> points)
{
	int i;
	vector <point3D> projPoints;
	point3D temp;
	Transformations tran;
	Vector resultant(1, 2, 3);
	float mat[4][4] = {
		{0,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	Matrix projectMat(mat);
	for (i = 0; i < points.size(); i++)
	{
		Vector dummyPoint(points[i].x, points[i].y, points[i].z);
		resultant = tran.multiplyWithCompo(projectMat, dummyPoint);
		temp.x = resultant.getVectorValue(0);
		temp.y = resultant.getVectorValue(1);
		temp.z = resultant.getVectorValue(2);
		projPoints.push_back(temp);
	}
	return projPoints;
}

int main()
{
	int i,j,t;
	char addchoice, axischoice, space, axisRot;
	vector <point3D> points;
	vector <point3D> outputXYProj, outputXZProj, outputYZProj, outDist, outRot;
	vector <float> readPoints;
	vector <int> transChoices;
	string indiv, filename, subs, ssubs, outName;
	float conv, xTrans, yTrans, zTrans, dist1, dist2, xSq, ySq, zSq, radians, axisOffset, normVal;
	float mDist[4][4], moTrans[4][4], mScal[4][4], mTrans[4][4], mSque[4][4], mRot[4][4];
	bool choice, willProject = false, isInverse = false;
	Transformations transf;
	point3D testbary, testout, arbitAxis;
	point2D test2d;
	Matrix dist(mDist);
	Matrix oTrans(moTrans);
	Matrix sque(mSque);
	Matrix rotate(mRot);
	Matrix rotateZarb(mRot);
	Matrix zInv(mRot), xInv(mRot), finalCompo(mRot), scal(mScal), trans(mTrans);

	cout << "What file would you like to open? ";
	cin >> filename;
	filename = filename + ".txt";
	ifstream setOfPoints(filename);
	
	//read coordinates from file
	while(getline(setOfPoints, indiv))
	{
		stringstream ss(indiv);
		while (ss.good())
		{
			i = 0;
			getline(ss, subs, ','); //prints a new line after the comma
			while (!isdigit(subs[i]) && subs[i] != '-')
			{
				i++;
			}
			ssubs = subs.substr(i, '\n');
			conv = stof(ssubs);
			cout << conv << endl;
			readPoints.push_back(conv);
		}
	}
	//end
	//assign read coordinates as point3d
	for (size_t i = 0; i < readPoints.size(); i+=3)
	{
		point3D pt;
		pt.x = readPoints[i];
		pt.y = readPoints[i + 1];
		pt.z = readPoints[i + 2];
		points.push_back(pt);
	}
	//end
	//generate vector matrix per point in points vector
	
	cout << endl << "What transformations would you like to do?" << endl;
	cout << "[1] Translate" << endl << "[2] Scale" << endl << "[3] Distort" << endl << "[4] Squeeze" << endl << "[5] Project" << endl << "[6] Rotate" << endl;
	choice = true;
	while (choice == true)
	{
		cout << endl << "Select your transformations:";
		cin >> t;
		transChoices.push_back(t);
		cout << "Do you want to add another? (y/n): ";
		cin >> addchoice;
		if (addchoice == 'y')
			choice = true;
		else
			choice = false;
	}
	
	transf.getScaleMatrix(2, 3, 2); // creates and displays a scale matrix that scales 2 in x, 3 in y, 2 in z
	transf.getTranslateMatrix(5, 3, 5); // creates and displays a trans matrix that moves 5 in x, 3 in y, 5 in z
	float testf[4][4] = {
		{1,2,3,0},
		{1,1,2,0},
		{1,1,1,0},   //try mo palitan values ng zero, matic pa rin siya nagcoconvert to homog
		{0,0,0,1}
	};
	float testf2[4][4] = {
		{1,2,3,0},
		{1,2,2,0},
		{2,1,1,0},	//try mo palitan values ng zero, matic pa rin siya nagcoconvert to homog
		{0,0,0,1}
	};
	Matrix testm1(testf);
	Matrix testm2(testf2);
	Vector testVector(1, 2, 3);
	transf.multiplyMatrix(testm1, testm2);
	transf.multiplyWithCompo(testf, testVector);
	cout << endl;
	//testbary = computeBarycenter(points);
	//cout << testbary.x << endl << testbary.y << endl << testbary.z;
	
	
	//projectXZ(points);
	//projectYZ(points);
	

	//perform transformations, return matrices
	for (i = 0; i < transChoices.size(); i++)
	{
		if (transChoices[i] == 1) //Translate
		{
			cout << endl << "How much in x,y,z do you want to translate?" << endl;
			cout << "X:";
			cin >> xTrans;
			cout << "Y:";
			cin >> yTrans;
			cout << "Z:";
			cin >> zTrans;
			trans = transf.getTranslateMatrix(xTrans, yTrans, zTrans); //trans is the translate matrix
		}
		if (transChoices[i] == 2) //Scale
		{
			Matrix oTrans(moTrans);
			cout << endl << "World space (w) or Object Space (o)? ";
			cin >> space;
			cout << endl << "How much in x,y,z do you want to scale?" << endl;
			cout << "X:";
			cin >> xTrans;
			cout << "Y:";
			cin >> yTrans;
			cout << "Z:";
			cin >> zTrans;
			if (space == 'o')
			{
				testbary = computeBarycenter(points);
				oTrans = transf.getTranslateMatrix(testbary.x * -1, testbary.y * -1, testbary.z * -1);
				scal = transf.getScaleMatrix(xTrans, yTrans, zTrans);
				scal = transf.multiplyMatrix(oTrans, scal);
				oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, testbary.z);
				scal = transf.multiplyMatrix(scal, oTrans);
			}
			else
				scal = transf.getScaleMatrix(xTrans, yTrans, zTrans); //scal is the scale matrix
		}
		if (transChoices[i] == 3) //Distort
		{
			cout << endl << "World space (w) or Object Space (o)? ";
			cin >> space;
			cout << endl << "In what axis do you want to distort?" << endl;
			cin >> axischoice;
			cout << "How much?" << endl;
			cout << "Amount 1 (xy/yx/zx): ";
			cin >> dist1;
			cout << "Amount 2 (xz/yz/zy): ";
			cin >> dist2;
			if (space == 'o')
			{
				testbary = computeBarycenter(points);
				oTrans = transf.getTranslateMatrix(testbary.x * -1, testbary.y * -1, testbary.z * -1);
				dist = transf.getDistortMatrix(axischoice, dist1, dist2);
				dist = transf.multiplyMatrix(oTrans, dist);
				oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, testbary.z);
				dist = transf.multiplyMatrix(dist, oTrans);
			}
			else
				dist = transf.getDistortMatrix(axischoice, dist1, dist2); //dist is the distort matrix
		}
		if (transChoices[i] == 4) //Squeeze
		{
			cout << endl << "How much in x,y,z do you want to squeeze?" << endl;
			cout << "X:";
			cin >> xSq;
			cout << "Y:";
			cin >> ySq;
			cout << "Z:";
			cin >> zSq;
			sque = transf.getSqueezeMatrix(xSq, ySq, zSq); //sque is the squeeze matrix
		}
		if (transChoices[i] == 5) //project
		{
			willProject = true;
			continue;
		}
		if (transChoices[i] == 6) //rotate
		{
			cout << "World space (w) or object space (o)?: ";
			cin >> space;
			cout << "Axis rotation (a) or Arbitrary Axis Rotation (r)? :";
			cin >> axisRot;
			if (axisRot == 'a')
			{
				cout << "What is the axis of your rotation? (x/y/z): ";
				cin >> axischoice;
				cout << "What is the angle of rotation? (in radians): ";
				cin >> radians;
				cout << "How many radians away from chosen axis is the rotation axis: ";  //from origin of axis 
				cin >> axisOffset;
				if (space == 'o')
				{
					testbary = computeBarycenter(points);
					if (axischoice == 'x')
						oTrans = transf.getTranslateMatrix((testbary.x - axisOffset) * -1, testbary.y, testbary.z);
					else if (axischoice == 'y')
						oTrans = transf.getTranslateMatrix(testbary.x, (testbary.y - axisOffset) * -1, testbary.z);
					else
						oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, (testbary.z - axisOffset) * -1);

					rotate = transf.getRotateMatrix(radians, axischoice, false);
					rotate = transf.multiplyMatrix(oTrans, rotate);

					if (axischoice == 'x')
						oTrans = transf.getTranslateMatrix(abs(testbary.x - axisOffset), testbary.y, testbary.z);
					else if (axischoice == 'y')
						oTrans = transf.getTranslateMatrix(testbary.x, abs(testbary.y - axisOffset), testbary.z);
					else
						oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, abs(testbary.z - axisOffset));

					rotate = transf.multiplyMatrix(rotate, oTrans);
				}
				else //if rotation is world space
				{
					rotate = transf.getRotateMatrix(radians, axischoice, false);
				}
			}
			else //arbitrary axis rotation
			{
				cout << "What is the angle of rotation? (in radians): ";
				cin >> radians;
				cout << "Vector Axis X: ";
				cin >> arbitAxis.x;
				cout << "Vector Axis Y: ";
				cin >> arbitAxis.y;
				cout << "Vector Axis Z: ";
				cin >> arbitAxis.z;
				normVal = transf.normalize(arbitAxis.x, arbitAxis.y, arbitAxis.z);
			
				/*
				testbary = computeBarycenter(points);
				oTrans = transf.getTranslateMatrix((testbary.x - arbitAxis.x ), (testbary.y - arbitAxis.y ), (testbary.z - arbitAxis.z ));
				rotate = transf.getRotateArbitrary(radians, arbitAxis.x/normVal, arbitAxis.y/normVal, arbitAxis.z/normVal);
				rotate = transf.multiplyMatrix(oTrans, rotate);
				*/
				
				/*
				
				testbary = computeBarycenter(points);

				oTrans = transf.getTranslateMatrix((testbary.x - arbitAxis.x/normVal) * -1, (testbary.y - arbitAxis.y/normVal) * -1, (testbary.z - arbitAxis.z/normVal) * -1); //trans to origin
				rotate = transf.getRotateMatrix(radians, 'x', false); //rotate about x
				rotate = transf.multiplyMatrix(oTrans, rotate); //compo trans and rotate x

				rotateZarb = transf.getRotateMatrix(radians, 'z', false); //rotate about z
				rotate = transf.multiplyMatrix(rotateZarb, rotate); //compo rotate z and rotate x and trans

				zInv = transf.getRotateMatrix(radians, 'z', true); //inverse rotate z
				rotate = transf.multiplyMatrix(zInv, rotate);

				xInv = transf.getRotateMatrix(radians, 'x', true); //inverse rotate x
				rotate = transf.multiplyMatrix(xInv, rotate);

				oTrans = transf.getTranslateMatrix(testbary.x/normVal, testbary.y/normVal, testbary.z/normVal);
				rotate = transf.multiplyMatrix(oTrans, rotate);
				//oTrans = transf.getTranslateMatrix(testbary.x , testbary.y, (testbary.z)); //back to orig place
				//rotate = transf.multiplyMatrix(oTrans, rotate);
				*/
				/*
				
				testbary = computeBarycenter(points);
				oTrans = transf.getTranslateMatrix(testbary.x * -1, testbary.y * -1, (testbary.z) * -1); //trans to origin
				rotate = transf.getRotateMatrix(radians, 'x'); //rotate about x
				rotate = transf.multiplyMatrix(oTrans, rotate);
				rotateYarb = transf.getRotateMatrix(radians, 'y'); //rotate about y
				rotate = transf.multiplyMatrix(rotate, rotateYarb);


				oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, (testbary.z));
				rotate = transf.multiplyMatrix(oTrans, rotate);
				*/
				//
				//rotate = transf.getRotateArbitrary(radians, arbitAxis.x, arbitAxis.y, arbitAxis.z);
			}
		}
	}
	//compose here after
	for (i = 0; i < points.size(); i++)
	{
		Vector p(points[i].x, points[i].y, points[i].z);
		Vector dummyV(1, 3, 5);
		point3D output;
		
		
		finalCompo = transf.multiplyMatrix(rotate, scal);
		finalCompo = transf.multiplyMatrix(finalCompo, trans);
		
		dummyV = transf.multiplyWithCompo(rotate, p);
		output.x = dummyV.getVectorValue(0);
		output.y = dummyV.getVectorValue(1);
		output.z = dummyV.getVectorValue(2);
		outRot.push_back(output);
	}
	
	
	//if (willProject == true)
	//{
		//call project fxn, nasa baba
	//}


	//write to a file yung final coord values
	cout << "What would you like to name the output file? ";
	cin >> outName;
	outName = outName + ".txt";
	ofstream pointsOut(outName);
	//print here yung results to the txt file
	for (i = 0; i < points.size(); i++)
	{
		pointsOut << outRot[i].x << ',' << outRot[i].y << "," << outRot[i].z << endl;
	}

	//close files
	setOfPoints.close();
	pointsOut.close();
	return 0;
}


/* DO NOT DELETE, FOR REFERENCE TO HAHAH
* for (j = 0; j < points.size(); j++)
			{
				Vector pTrans(points[j].x, points[j].y, points[j].z);

			}
*/
/* GET ROW TEST

	Matrix test(testf);  //creates a new 4x4 matrix
	Vector testv(2,3,4);  // creates a dummy 4x1 vector
	testv.displayVector();   //displays the dummy vector
	testv = testv.getRow(testf, 1);  //assigns the get row to the dummy vector, getRow params: matrix testf, row na gusto mo
	testv.displayVector();  // displays the new vector, yung nakuhang row from testf

*/
/* GENERATES A VECTOR FROM POINTS

	Vector p(points[0].x, points[0].y, points[0].z); //creates a 4x1 column matrix na nagcocontain ng x,y,z and homog coords
	Vector p2(points[1].x, points[1].y, points[1].z);
	p.displayVector();
	cout << endl;
	p2.displayVector();
	cout << endl;
	cout << "dot prod:" << transf.dotProd(p, p2) << endl;     //MAKES THE DOT PRODUCT

	*/

/* FOR XY, XZ, YZ PROJECTION

		for (i = 0; i < points.size(); i++)
		{
			vector <point3D> outputPts(projectXY(points));
			pointsOut << outputPts[i].x << "," << outputPts[i].y << "," << outputPts[i].z << endl;
			outputXYProj.push_back(outputPts[i]);
		}

		outputXYProj holds all FINAL projected points, write na lang siya to the file
	*/

/* FOR PRINTING DISTORT VALUES TO TXT FILE

		for (i = 0; i < points.size(); i++)
		{
			pointsOut << outDist[i].x << ',' << outDist[i].y << "," << outDist[i].z << endl;
		}
		*/

/* F0R GETTING FINAL VALUES OF DISTORT
* for (i = 0; i < points.size(); i++)
	{
		Vector p(points[i].x, points[i].y, points[i].z);
		Vector dummyV(1, 3, 5);
		point3D output;
		dummyV = transf.multiplyWithCompo(dist,p);
		output.x = dummyV.getVectorValue(0);
		output.y = dummyV.getVectorValue(1);
		output.z = dummyV.getVectorValue(2);
		outDist.push_back(output);
	}
*/