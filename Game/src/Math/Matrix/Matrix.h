#pragma once
//#include "..\\Graphics3D\Vector3.h"

class Matrix
{
public:
  const static Matrix PROJ_MAT;
	
    float m[4][4];
	Matrix();

    float &operator() (int row, int col);

	Matrix operator* (const Matrix &matrix);
    Matrix operator*= (const Matrix &matrix);

    static Matrix Identity();

    //static Matrix Translate (Vector3 &v);

	static Matrix MakeProjectionMatrix (float fNear = 0.1f, float fFar = 1000.0f, float fFov = 90.0f);

    static Matrix Matrix_MakeRotationX (float fAngleRad);
    static Matrix Matrix_MakeRotationY (float fAngleRad);
    static Matrix Matrix_MakeRotationZ (float fAngleRad);
};