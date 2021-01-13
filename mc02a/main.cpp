/*
* GD-MATH MC02A LINEAR TRANSFORMATION ON 3D POINTS
* DEVELOPERS:
*	GAURANA, ALDREY
*	TALLADOR, ERYN
* 
* LAST MODIFIED: 1/12/2021
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

using namespace std;

typedef struct point3D
{
	float x;
	float y;
	float z;
}point3D;

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

int main()
{
	int i,j,t, compoIndex = 0, projectChoice;
	char addchoice, axischoice, space, axisRot;
	vector <point3D> points;
	vector <point3D> outRot;
	vector <float> readPoints;
	vector <int> transChoices;
	vector <Matrix> forCompo;
	string indiv, filename, subs, ssubs;
	float conv, xTrans, yTrans, zTrans, dist1, dist2, xSq, ySq, zSq, radians, axisOffset, normVal;
	float mStruct[4][4];
	bool choice, isInverse = false, isSpherical = false;
	Transformations transf;
	point3D testbary, arbitAxis;
	Matrix dist(mStruct), oTrans(mStruct), finalCompo(mStruct), sque(mStruct), rotate(mStruct);
	Matrix scal(mStruct), translateMatrix(mStruct), coordPts(mStruct), finalPts(mStruct);

	cout << "What file would you like to open? ";
	cin >> filename;
	filename = filename + ".txt";
	ifstream setOfPoints(filename);
	if (setOfPoints.fail())
	{
		cout << endl << "ERROR: FILE NOT FOUND. TERMINATING." << endl;
		return 0; 
	}

	
	//PARSE AND READ COORDINATES FROM FILE
	while(getline(setOfPoints, indiv))
	{
		stringstream ss(indiv);
		while (ss.good())
		{
			i = 0;
			getline(ss, subs, ','); //comma is the delim

			//CHECKS IF INPUT FILE HAS SPHERICAL COORDS, OTHERWISE, SPHERICAL = FALSE
			if (subs[i] == 's')
				isSpherical = true;

			while (!isdigit(subs[i]) && subs[i] != '-')
			{
				i++;
			}
			//EXTRACTS THE NUMERICAL STRING
			ssubs = subs.substr(i, '\n');
			//CONVERTS THE STRING TO FLOAT VALUE
			conv = stof(ssubs); 
			//ADD THE VALUE TO POINTS VECTOR
			readPoints.push_back(conv);
		}
	}
	//end

	//ASSIGN READ POINTS AS POINT3D
	for (size_t i = 0; i < readPoints.size(); i+=3)
	{
		point3D pt;

		//CONVERSION OF SPHERICAL TO CARTESIAN
		if (isSpherical == true)
		{
			pt.x = readPoints[i] * sin(readPoints[i+1]) * cos(readPoints[i + 2]);
			pt.y = readPoints[i] * sin(readPoints[i + 1]) * sin(readPoints[i + 2]);
			pt.z = readPoints[i] * cos(readPoints[i + 1]);
		}
		//CARTESIAN COORDS GET ASSIGNED TO POINT3D
		else
		{
			pt.x = readPoints[i];
			pt.y = readPoints[i + 1];
			pt.z = readPoints[i + 2];
		}
		//A POINT3D IS INSERTED TO POINTS VECTOR THAT ACCEPTS POINT3D
		points.push_back(pt);
	}
	//end
	
	//ASK USER FOR DESIRED TRANSFORMATIONS
	cout << endl << "What transformations would you like to do?" << endl;
	cout << "[1] Translate" << endl << "[2] Scale" << endl << "[3] Distort" << endl << "[4] Squeeze" << endl << "[5] Project" << endl << "[6] Rotate" << endl;
	choice = true;

	//PERFORM LOOP UNTIL USER ENTERS 'n'
	while (choice == true)
	{
		do {
			cout << endl << "Select your transformations:";
			cin >> t;
		} while (t < 1 || t > 6);

		//CHOICES INPUTTED BY USER GETS INSERTED TO TRANSCHOICES VECTOR
		transChoices.push_back(t);

		do {
			cout << "Do you want to add another? (y/n): ";
			cin >> addchoice;
			addchoice = tolower(addchoice);
		} while (addchoice != 'y' && addchoice != 'n');

		if (addchoice == 'y')
			choice = true;
		else
			choice = false;
	}
	
	//PERFORM THE TRANSFORMATIONS DESIRED
	//RETURN TRANSFORM MATRICES TO BE FED TO FORCOMPO VECTOR
	for (i = 0; i < transChoices.size(); i++)
	{
		if (transChoices[i] == 1) //TRANSLATION
		{
			cout << "=================" << endl << "TRANSLATION" << endl << "=================" << endl;
			cout << "How much in x,y,z do you want to translate?" << endl;
			cout << "X:";
			cin >> xTrans;
			cout << "Y:";
			cin >> yTrans;
			cout << "Z:";
			cin >> zTrans;
			forCompo.push_back(transf.getTranslateMatrix(xTrans, yTrans, zTrans));
			//trans is the translate matrix pushed to the forCompo list
		}
		if (transChoices[i] == 2) //SCALING
		{
			Matrix oTrans(mStruct);
			cout << "=================" << endl << "SCALING" << endl << "=================" << endl;
			cout << "World space (w) or Object Space (o)? ";
			cin >> space;
			cout << endl << "How much in x,y,z do you want to scale?" << endl;
			cout << "X:";
			cin >> xTrans;
			cout << "Y:";
			cin >> yTrans;
			cout << "Z:";
			cin >> zTrans;
			if (space == 'o') //for object space
			{
				testbary = computeBarycenter(points);
				oTrans = transf.getTranslateMatrix(testbary.x * -1, testbary.y * -1, testbary.z * -1);
				scal = transf.getScaleMatrix(xTrans, yTrans, zTrans);
				scal = transf.multiplyMatrix(oTrans, scal, false);
				oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, testbary.z);

				forCompo.push_back(transf.multiplyMatrix(scal, oTrans, false));
				//scal is the scale matrix, pushed to the forcompo list
			}
			else //for world space
				forCompo.push_back(transf.getScaleMatrix(xTrans, yTrans, zTrans));
		}
		if (transChoices[i] == 3) //DISTORTION
		{
			cout << "=================" << endl << "DISTORTION" << endl << "=================" << endl;
			cout << "World space (w) or Object Space (o)? ";
			cin >> space;
			cout << endl << "In what axis do you want to distort?" << endl;
			cin >> axischoice;
			cout << "How much?" << endl;

			//distort on the indicated planes, based on the reference book
			// X: xy/xz distort, Y: yx/yz distort, Z: zx/zy distort

			cout << "Amount 1 (xy/yx/zx): ";  
			cin >> dist1;
			cout << "Amount 2 (xz/yz/zy): ";
			cin >> dist2;
			if (space == 'o') //for object space
			{
				testbary = computeBarycenter(points);
				oTrans = transf.getTranslateMatrix(testbary.x * -1, testbary.y * -1, testbary.z * -1);
				dist = transf.getDistortMatrix(axischoice, dist1, dist2);
				dist = transf.multiplyMatrix(oTrans, dist, false);
				oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, testbary.z);

				forCompo.push_back(transf.multiplyMatrix(dist, oTrans, false));
				//dist is the distort matrix, pushed to the forcompo list
			}
			else //for world space
				forCompo.push_back(transf.getDistortMatrix(axischoice, dist1, dist2));
		}
		if (transChoices[i] == 4) //SQUEEZE
		{
			cout << "=================" << endl << "SQUEEZE" << endl << "=================" << endl;
			cout << "How much in x,y,z do you want to squeeze?" << endl;
			cout << "X:";
			cin >> xSq;
			cout << "Y:";
			cin >> ySq;
			cout << "Z:";
			cin >> zSq;
			forCompo.push_back(transf.getSqueezeMatrix(xSq, ySq, zSq));
			//sque is the squeeze matrix, pushed to the forcompo list
		}
		if (transChoices[i] == 5) //PROJECT
		{
			cout << "=================" << endl << "PROJECTION" << endl << "=================" << endl;
			cout << "What plane do you want to project to?" << endl;
			cout << "[1] XY Plane" << endl;
			cout << "[2] XZ Plane" << endl;
			cout << "[3] YZ Plane" << endl;
			cout << "Choice: ";
			cin >> projectChoice;
			forCompo.push_back(transf.project(projectChoice));
		}
		if (transChoices[i] == 6) //ROTATION
		{
			cout << "=================" << endl << "ROTATION" << endl << "=================" << endl;
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
				cout << "How many radians away from chosen axis is the rotation axis: ";  //from origin of chosen axis 
				cin >> axisOffset;
				if (space == 'o') //if object space
				{
					testbary = computeBarycenter(points);

					//translate to object origin
					if (axischoice == 'x')
						oTrans = transf.getTranslateMatrix((testbary.x - axisOffset) * -1, testbary.y, testbary.z);
					else if (axischoice == 'y')
						oTrans = transf.getTranslateMatrix(testbary.x, (testbary.y - axisOffset) * -1, testbary.z);
					else
						oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, (testbary.z - axisOffset) * -1);

					//perform rotation
					if (axischoice == 'x')
						rotate = transf.getRotateQuaternions(radians, 1, 0, 0);
					if(axischoice == 'y')
						rotate = transf.getRotateQuaternions(radians, 0, 1, 0);
					if (axischoice == 'z')
						rotate = transf.getRotateQuaternions(radians, 0, 0, 1);
					
					//update rotate, it is now the product of the translation and rotation
					rotate = transf.multiplyMatrix(oTrans, rotate, false);

					//translate back to object's original position
					if (axischoice == 'x')
						oTrans = transf.getTranslateMatrix(abs(testbary.x - axisOffset), testbary.y, testbary.z);
					else if (axischoice == 'y')
						oTrans = transf.getTranslateMatrix(testbary.x, abs(testbary.y - axisOffset), testbary.z);
					else
						oTrans = transf.getTranslateMatrix(testbary.x, testbary.y, abs(testbary.z - axisOffset));

					
					forCompo.push_back(transf.multiplyMatrix(rotate, oTrans, false));
					//rotate is the rotate matrix, pushed to the forcompo list
				}
				else //if rotation is world space
				{
					if (axischoice == 'x')
						forCompo.push_back(transf.getRotateQuaternions(radians, 1, 0, 0));
					if (axischoice == 'y')
						forCompo.push_back(transf.getRotateQuaternions(radians, 0, 1, 0));
					if (axischoice == 'z')
						forCompo.push_back(transf.getRotateQuaternions(radians, 0, 0, 1));
					//rotate is the rotate matrix, pushed to the forcompo list
				}
			}
			else //USER CHOSE ARBITRARY AXIS ROTATION
			{
				cout << "What is the angle of rotation? (in radians): ";
				cin >> radians;
				cout << "Vector Axis X: ";
				cin >> arbitAxis.x;
				cout << "Vector Axis Y: ";
				cin >> arbitAxis.y;
				cout << "Vector Axis Z: ";
				cin >> arbitAxis.z;

				forCompo.push_back(transf.getRotateQuaternions(radians,arbitAxis.x, arbitAxis.y, arbitAxis.z));
			}
		}
	}

	//MAKE THE FINAL COMPOSED MATRIX
	finalCompo.get3DIdentity();
	for (compoIndex = 0; compoIndex < forCompo.size() ; compoIndex++)
	{
		//loop on all transformation matrices and multiply
		finalCompo = transf.multiplyMatrix(forCompo[compoIndex], finalCompo, false); //forCompo[compoIndex], finalCompo,
	}

	//MULTIPLY THE FINAL COMPOSED MATRIX TO THE COORDINATES
	for (i = 0; i < points.size(); i++)
	{
		Vector p(points[i].x, points[i].y, points[i].z);
		Vector dummyV(1, 3, 5);
		point3D output;
		
		coordPts.get3DIdentity();
		coordPts.setIndexVal(0, 0, points[i].x);
		coordPts.setIndexVal(1, 0, points[i].y);
		coordPts.setIndexVal(2, 0, points[i].z);
		coordPts.setIndexVal(3, 0, 1);

		finalCompo.displayMatrix();
		finalPts = transf.multiplyMatrix(finalCompo, coordPts, true);

		//assign the answers to point3d
		output.x = finalPts.getIndexVal(0, 0);
		output.y = finalPts.getIndexVal(1, 0);
		output.z = finalPts.getIndexVal(2, 0);
		outRot.push_back(output);
	}
	
	//CREATE OUTPUT FILE
	ofstream pointsOut("output.txt");
	if (pointsOut.fail())
	{
		cout << "ERROR: CANNOT MAKE OUTPUT FILE. TERMINATING." << endl;
	}
	//print results to the txt file
	for (i = 0; i < points.size(); i++)
	{
		pointsOut << outRot[i].x << ',' << outRot[i].y << "," << outRot[i].z << endl;
	}

	//close files
	setOfPoints.close();
	pointsOut.close();
	return 0;
}
