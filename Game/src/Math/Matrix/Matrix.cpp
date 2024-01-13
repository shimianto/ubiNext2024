#include "stdafx.h"
#include "Matrix.h"
#include <App/AppSettings.h>
#include "..\Vector3\Vector3.h"

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
