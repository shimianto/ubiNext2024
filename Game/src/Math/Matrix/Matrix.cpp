#include "stdafx.h"
#include "Matrix.h"
#include <App/AppSettings.h>
#include "..\Vector3\Vector3.h"

const Matrix Matrix::PROJ_MAT = Matrix::MakeProjectionMatrix();

Matrix::Matrix() : m{0.0f}
{
}

float &Matrix::operator() (int row, int col)
{
  return m[row][col];
}

Matrix Matrix::operator* (const Matrix &matrix)
{
  Matrix outMat;
  for (int c = 0; c < 4; c++) 
  {
	for (int r = 0; r < 4; r++) {
	  outMat.m[r][c] =
	    this->m[r][0] * matrix.m[0][c] + this->m[r][1] * matrix.m[1][c] + this->m[r][2] * matrix.m[2][c] + this->m[r][3] * matrix.m[3][c];
	}
  }
  return outMat;
}

Matrix Matrix::operator*= (const Matrix &matrix)
{
  return *this * matrix;
}

Matrix Matrix::Identity()
{
  Matrix matrix;
  matrix (0, 0) = 1.0f;
  matrix (1, 1) = 1.0f;
  matrix (2, 2) = 1.0f;
  matrix (3, 3) = 1.0f;
  return matrix;
}

Matrix Matrix::Translate (Vector3 &v)
{
  Matrix matrix = Matrix::Identity();
  matrix (3, 0) = v.x;
  matrix (3, 1) = v.y;
  matrix (3, 2) = v.z;
  return matrix;
}

Matrix Matrix::MakeProjectionMatrix (float fNear, float fFar, float fFov)
{
  Matrix proj;
  float fAspectRatio = (float)APP_INIT_WINDOW_HEIGHT / (float)APP_INIT_WINDOW_WIDTH;
  float fFovRad = 1.0f / tanf (fFov * 0.5f / 180.0f * 3.14159f);

  proj.m[0][0] = fAspectRatio * fFovRad;
  proj.m[1][1] = fFovRad;
  proj.m[2][2] = fFar / (fFar - fNear);
  proj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
  proj.m[2][3] = 1.0f;
  proj.m[3][3] = 0.0f;

  return proj;
}

Matrix Matrix::MakeRotationMatrixX (float fAngleRad)
{
  Matrix matrix;
  matrix.m[0][0] = 1.0f;
  matrix.m[1][1] = cosf (fAngleRad);
  matrix.m[1][2] = sinf (fAngleRad);
  matrix.m[2][1] = -sinf (fAngleRad);
  matrix.m[2][2] = cosf (fAngleRad);
  matrix.m[3][3] = 1.0f;
  return matrix;
}

Matrix Matrix::MakeRotationMatrixY (float fAngleRad)
{
  Matrix matrix;
  matrix.m[0][0] = cosf (fAngleRad);
  matrix.m[0][2] = sinf (fAngleRad);
  matrix.m[2][0] = -sinf (fAngleRad);
  matrix.m[1][1] = 1.0f;
  matrix.m[2][2] = cosf (fAngleRad);
  matrix.m[3][3] = 1.0f;
  return matrix;
}

Matrix Matrix::MakeRotationMatrixZ (float fAngleRad)
{
  Matrix matrix;
  matrix.m[0][0] = cosf (fAngleRad);
  matrix.m[0][1] = sinf (fAngleRad);
  matrix.m[1][0] = -sinf (fAngleRad);
  matrix.m[1][1] = cosf (fAngleRad);
  matrix.m[2][2] = 1.0f;
  matrix.m[3][3] = 1.0f;
  return matrix;
}
