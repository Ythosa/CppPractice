#pragma once

const int MATRIX_SIZE = 3;
typedef std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE> matrix;

bool GetMatrix(std::ifstream & inputFile, matrix & gettingMatrix);
void PrintMatrix(const matrix & outMatrix);
matrix MultyplyMatrix(const matrix & matrix1, const matrix & matrix2);