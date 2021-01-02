/*needed to be addressed:
* 
* address natin muna yung matrix multiplication fxn tsaka tayo sa rotation
* pwede mo paglaruan yung test calls para makuha mo feel ng fxns
*/

#include<iostream>
#include<iomanip>
#include<cmath>
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
	int i,j,trans;
	char addchoice, axischoice, space;
	vector <point3D> points;
	vector <point3D> outputXYProj, outputXZProj, outputYZProj, outDist;
	vector <float> readPoints;
	vector <int> transChoices;
	string indiv, filename, subs, ssubs, outName;
	float conv, xTrans, yTrans, zTrans, dist1, dist2, xSq, ySq, zSq;
	float mDist[4][4], moTrans[4][4], mScal[4][4], mTrans[4][4];
	bool choice, willProject;
	Transformations transf;
	point3D testbary, testout;
	point2D test2d;
	Matrix dist(mDist);
	Matrix oTrans(moTrans);

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
		cin >> trans;
		transChoices.push_back(trans);
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
			Matrix trans(mTrans);
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
			Matrix scal(mScal);
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
			float mSque[4][4];
			Matrix sque(mSque);
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
	}
	//compose here after
	
	
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